/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:32:59 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 19:13:22 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "events.h"
#include "libft.h"

static void	ray_caster(t_window *w, t_vec2 coord, float fov)
{
	t_ray		ray;
	t_color		color;

	calculate_ray(&ray, w, &coord, fov);
	color = cast_ray(w, ray, 0);
	if (OS[0] == 'D')
		mlx_pixel_put(w->mlx_ptr, w->window, coord.x, coord.y,
			(color.r << 16) | (color.g << 8) | color.b);
	else
		custom_mlx_pixel_put(&w->img,
			coord.x, coord.y,
			(color.r << 16) | (color.g << 8) | color.b);
}

static void	init_rt(t_window **window_ptr)
{
	t_window	*w;

	w = *window_ptr;
	w->fov = w->scene->camera.fov * M_PI / 180;
	if (OS[0] != 'D')
	{
		w->img.img = mlx_new_image(w->mlx_ptr, w->width, w->height);
		w->img.addr = mlx_get_data_addr(w->img.img, &w->img.bits_per_pixel,
				&w->img.line_length, &w->img.endian);
	}
	else
		mlx_clear_window(w->mlx_ptr, w->window);
}

void	render_scene(t_window **window_ptr)
{
	t_vec2		coord;
	t_window	*w;

	w = *window_ptr;
	init_rt(window_ptr);
	coord.y = 0;
	while (coord.y <= w->height)
	{
		coord.x = 0;
		while (coord.x <= w->width)
		{
			ray_caster(w, coord, w->fov);
			coord.x++;
		}
		coord.y++;
	}
	if (OS[0] != 'D')
	{
		mlx_clear_window(w->mlx_ptr, w->window);
		mlx_put_image_to_window(w->mlx_ptr, w->window, w->img.img, 0, 0);
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
	window->transform.type = 'f';
	keyboard_conf(window);
	lookat(window);
	mlx_key_hook(window->window, key_event, window);
	mlx_hook(window->window, DESTROY_NOTIFY, 1L << 0, quit_game, window);
	mlx_hook(window->window, BUTTON_PRESS, 1L << 2, mousedown, window);
	mlx_hook(window->window, EXPOSE, 1L << 15, unminimize, window);
	render_scene(&window);
	mlx_loop(window->mlx_ptr);
	return ;
}
