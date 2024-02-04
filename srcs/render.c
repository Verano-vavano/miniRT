/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:32:59 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 08:52:46 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

double	trace(t_scene *scene, t_ray ray, t_lform *lform, bool planes)
{
	double	x;
	double	x_near;
	t_lform	temp;

	x_near = INFINITY;
	if (sp_render(scene->spheres, ray, &x, lform))
		x_near = x;
	if (planes && pl_render(scene->planes, ray, &x, &temp) && x < x_near)
	{
		x_near = x;
		*lform = temp;
	}
	if (cyl_render(scene->cyl, ray, &x, &temp) && x < x_near)
	{
		x_near = x;
		*lform = temp;
	}
	return (x_near);
}

t_color	cast_ray(t_window *window, t_ray ray, int ray_num)
{
	t_scene		*scene;
	double		x_near;
	t_color		ret;
	t_col01		amb_contr, lgt_contr;
	t_lform		last_form;

	lgt_contr.r = 0;
	lgt_contr.g = 0;
	lgt_contr.b = 0;
	amb_contr.r = 0;
	amb_contr.g = 0;
	amb_contr.b = 0;
	scene = window->scene;
	last_form.addr = NULL;
	x_near = trace(scene, ray, &last_form, true);
	if (x_near > NEAR_CLIP && x_near < FAR_CLIP && last_form.addr != NULL)
	{
		t_vec3	hit = vec3_add(ray.org, vec3_mult_float(ray.dir, x_near));
		get_infos(hit, &last_form);
		if (last_form.shade && last_form.shade->reflect && ray_num < MAX_REFLECTION)
		{
			ret = reflect_color(window, hit, ray.dir, &last_form, ray_num);
			last_form.color.r = ret.r / 255.f;
			last_form.color.g = ret.g / 255.f;
			last_form.color.b = ret.b / 255.f;
		}
		ambient_lighting(scene->ambient, &amb_contr, last_form.color);
		dir_lighting(scene, hit, &lgt_contr, &last_form);
		sph_lighting(scene, hit, &lgt_contr, &last_form);
	}
	ret.r = (fmin(1.f, lgt_contr.r + amb_contr.r)) * 255;
	ret.g = (fmin(1.f, lgt_contr.g + amb_contr.g)) * 255;
	ret.b = (fmin(1.f, lgt_contr.b + amb_contr.b)) * 255;
	return (ret);
}

static t_vec3	cam2world(float m[4][4], t_vec3 *v)
{
		t_vec3	dst;

		dst.x = v->x * m[0][0] + v->y * m[1][0] + v->z * m[2][0];
		dst.y = v->x * m[0][1] + v->y * m[1][1] + v->z * m[2][1];
		dst.z = v->x * m[0][2] + v->y * m[1][2] + v->z * m[2][2];
		return (dst);
}

void	calculate_ray(t_ray *ray, t_window *window, t_vec2 *coord, float fov)
{
	ray->org = window->scene->camera.vp;
	ray->dir.x = (2.0f * (coord->x + 0.5f) / window->width - 1.0f) * window->aspect_ratio * tan(fov / 2);
	ray->dir.y = (1.0f - 2.0f * (coord->y + 0.5f) / window->height) * tan(fov / 2);
	ray->dir.z = 1;
	ray->dir = cam2world(window->cam, &ray->dir);
	ray->dir = vec3_normalize(ray->dir);
	return ;
}

void	render_scene(t_window **window_ptr)
{
	t_vec2		coord;
	t_ray		ray;
	t_color		color;
	t_window	*window;
	float		fov;

	window = *window_ptr;
	fov = window->scene->camera.fov * M_PI / 180;
	if (OS[0] != 'D')
	{
		window->img.img = mlx_new_image(window->mlx_ptr, window->width, window->height);
		window->img.addr = mlx_get_data_addr(window->img.img, &window->img.bits_per_pixel, &window->img.line_length, &window->img.endian);
	}
	else
		mlx_clear_window(window->mlx_ptr, window->window);
	coord.y = 0;
	while (coord.y <= window->height)
	{
		coord.x = 0;
		while (coord.x <= window->width)
		{
			calculate_ray(&ray, window, &coord, fov);
			color = cast_ray(window, ray, 0);
			if (OS[0] == 'D')
				mlx_pixel_put(window->mlx_ptr, window->window, coord.x, coord.y, (color.r << 16) | (color.g << 8) | color.b);
			else
				custom_mlx_pixel_put(&window->img,
				coord.x, coord.y,
				(color.r << 16) | (color.g << 8) | color.b);
			coord.x++;
		}
		coord.y++;
	}
	if (OS[0] != 'D')
	{
		mlx_clear_window(window->mlx_ptr, window->window);
		mlx_put_image_to_window(window->mlx_ptr, window->window, window->img.img, 0, 0);
	}
	return ;
}

inline t_vec3	calc_ray_point(t_ray ray, double hit)
{
	return (vec3_add(ray.org, vec3_mult_float(ray.dir, hit)));
}

void	lookat(t_window *window)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	tmp;

	tmp.x = 0;
	tmp.y = 1;
	tmp.z = 0;
	forward = window->scene->camera.dir;
	if (forward.x == 0 && forward.y == 0 && forward.z == 0)
		forward.z = 1;
	forward = vec3_normalize(forward);
	right = vec3_cross(tmp, forward);
	up = vec3_cross(forward, right);
	window->cam[0][0] = right.x;
	window->cam[0][1] = right.y;
	window->cam[0][2] = right.z;
	window->cam[1][0] = up.x;
	window->cam[1][1] = up.y;
	window->cam[1][2] = up.z;
	window->cam[2][0] = forward.x;
	window->cam[2][1] = forward.y;
	window->cam[2][2] = forward.z;
}

static int	unminimize(t_window *window)
{
	mlx_clear_window(window->mlx_ptr, window->window);
	mlx_put_image_to_window(window->mlx_ptr, window->window, window->img.img, 0, 0);
	return (0);
}

void	render(t_scene *scene)
{
	t_window	*window;

	window = ft_calloc(1, sizeof (t_window));
	if (!window)
		return ;
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
		return ;
	window->scene = scene;
	window->width = WIDTH;
	window->height = HEIGHT;
	window->aspect_ratio = (double) window->width / (double) window->height;
	window->window = mlx_new_window(window->mlx_ptr,
		window->width, window->height, "Cyberpunk");
	keyboard_conf(window);
	lookat(window);
	mlx_key_hook(window->window, key_event, window);
	mlx_hook(window->window, 17, 1L << 0, quit_game, window);
	mlx_hook(window->window, 4, 1L << 2, mousedown, window);
	mlx_hook(window->window, 12, 1L << 15, unminimize, window);
	render_scene(&window);
	mlx_loop(window->mlx_ptr);
	return ;
}
