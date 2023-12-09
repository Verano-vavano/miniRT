/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:32:59 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/09 00:22:01 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

static void	render_scene(t_window *window)
{
	t_vec2	coord;
	t_color	color;

	coord.y = 0;
	while (coord.y <= window->height)
	{
		coord.x = 0;
		while (coord.x <= window->width)
		{
			color = cast_ray(window, &coord);
			custom_mlx_pixel_put(&window->img,
				coord.x, coord.y,
				(color.r << 16) | (color.g << 8) | color.b);
			coord.x++;
		}
		coord.y++;
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
		window->width, window->height, "miniRT");
	window->img.img = mlx_new_image(window->mlx_ptr, window->width, window->height);
	window->img.addr = mlx_get_data_addr(window->img.img, &window->img.bits_per_pixel, &window->img.line_length, &window->img.endian);
	mlx_hook(window->window, 17, 1L << 0, quit_game, window);
	render_scene(window);
	mlx_put_image_to_window(window->mlx_ptr, window->window, window->img.img, 0, 0);
	mlx_loop(window->mlx_ptr);
	return ;
}
