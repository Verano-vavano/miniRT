/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:32:59 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/24 12:16:54 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

static t_color	cast_ray(t_window *window, t_vec2 *coord, float fov)
{
	t_scene		*scene;
	t_vec3		direction;
	double		x_near;
	double		x;
	t_color		ret;
	t_lform		last_form;

	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	scene = window->scene;
	direction.x = (2.0f * (coord->x + 0.5f) / window->width - 1.0f) * window->aspect_ratio * tan(fov / 2);
	direction.y = (1.0f - 2.0f * (coord->y + 0.5f) / window->height) * tan(fov / 2);
	direction.z = scene->camera.dir.z;
	direction = vec3_normalize(direction);
	x_near = INFINITY;
	last_form.addr = NULL;
	if (spheres_render_all(scene->spheres, scene->camera.vp, direction, &x, &last_form) && x < x_near)
		x_near = x;
	if (planes_render_all(scene->planes, scene->camera.vp, direction, &x, &last_form) && x < x_near)
		x_near = x;
	if (last_form.addr != NULL)
	{
		t_vec3	hit = vec3_normalize(vec3_add(scene->camera.vp, vec3_mult_float(direction, x_near)));
		ret = light_pathing(scene, hit, &last_form);
	}
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
