/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:32:59 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/24 02:30:46 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

double	trace(t_scene *scene, t_ray ray, t_lform *lform)
{
	double	x;
	double	x_near;
	t_lform	temp;

	x_near = INFINITY;
	if (sp_render(scene->spheres, ray, &x, lform))
		x_near = x;
	if (pl_render(scene->planes, ray, &x, &temp) && x < x_near)
	{
		x_near = x;
		*lform = temp;
	}
	return (x_near);
}

static t_color	cast_ray(t_window *window, t_vec2 *coord, float fov)
{
	t_scene		*scene;
	t_ray		ray;
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
	ray.org = scene->camera.vp;
	ray.dir.x = (2.0f * (coord->x + 0.5f) / window->width - 1.0f) * window->aspect_ratio * tan(fov / 2);
	ray.dir.y = (1.0f - 2.0f * (coord->y + 0.5f) / window->height) * tan(fov / 2);
	ray.dir.z = scene->camera.dir.z;
	ray.dir = vec3_normalize(ray.dir);
	last_form.addr = NULL;
	x_near = trace(scene, ray, &last_form);
	if (last_form.addr != NULL)
	{
		t_vec3	hit = vec3_add(ray.org, vec3_mult_float(ray.dir, x_near));
		get_infos(hit, &last_form, &(last_form.normal), &(last_form.color));
		ambient_lighting(scene->ambient, &amb_contr, last_form.color);
		dir_lighting(scene, hit, &lgt_contr, &last_form);
		//sph_lighting(scene, hit, &lgt_contr, &last_form);
	}
	ret.r = (fmin(1.f, lgt_contr.r + amb_contr.r)) * 255;
	ret.g = (fmin(1.f, lgt_contr.g + amb_contr.g)) * 255;
	ret.b = (fmin(1.f, lgt_contr.b + amb_contr.b)) * 255;
	return (ret);
}

void	render_scene(t_window **window_ptr)
{
	t_vec2		coord;
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
			color = cast_ray(window, &coord, fov);
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
	window->width = 720;
	window->height = 480;
	window->aspect_ratio = (double) window->width / (double) window->height;
	window->window = mlx_new_window(window->mlx_ptr,
		window->width, window->height, "Cyberpunk");
	mlx_key_hook(window->window, key_event, window);
	mlx_hook(window->window, 17, 1L << 0, quit_game, window);
	render_scene(&window);
	mlx_loop(window->mlx_ptr);
	return ;
}
