/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:32:59 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 16:55:01 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

t_hit	trace(t_scene *scene, t_ray ray, t_lform *lform, bool planes)
{
	t_lform	temp_lf;
	t_hit	hit;
	t_hit	temp_hit;

	hit.has_hit = false;
	hit.t = INFINITY;
	temp_hit.t = INFINITY;
	if (sp_render(scene->spheres, ray, &temp_hit, lform))
	{
		hit = temp_hit;
		hit.has_hit = true;
	}
	temp_hit.t = INFINITY;
	if (planes && pl_render(scene->planes, ray, &temp_hit, &temp_lf) && temp_hit.t < hit.t)
	{
		hit = temp_hit;
		*lform = temp_lf;
		hit.has_hit = true;
	}
	temp_hit.t = INFINITY;
	if (cyl_render(scene->cyl, ray, &temp_hit, &temp_lf) && temp_hit.t < hit.t)
	{
		hit = temp_hit;
		*lform = temp_lf;
		hit.has_hit = true;
	}
	return (hit);
}

t_color	cast_ray(t_window *window, t_ray ray, int ray_num)
{
	t_scene		*scene;
	t_hit		hit;
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
	hit.shade = NULL;
	hit = trace(scene, ray, &last_form, true);
	(void) ray_num;
	if (hit.t > NEAR_CLIP && hit.t < FAR_CLIP && last_form.addr != NULL)
	{
		/*if (hit.shade && hit.shade->reflect && ray_num < MAX_REFLECTION)
		{
			ret = reflect_color(window, hit, ray.dir, ray_num);
			hit.color.r = ret.r / 255.f;
			hit.color.g = ret.g / 255.f;
			hit.color.b = ret.b / 255.f;
		}*/
		ambient_lighting(scene->ambient, &amb_contr, hit.color);
		dir_lighting(scene, &hit, &lgt_contr);
		sph_lighting(scene, &hit, &lgt_contr);
	}
	ret.r = (fmin(1.f, lgt_contr.r + amb_contr.r)) * 255;
	ret.g = (fmin(1.f, lgt_contr.g + amb_contr.g)) * 255;
	ret.b = (fmin(1.f, lgt_contr.b + amb_contr.b)) * 255;
	return (ret);
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
