/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:32:59 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/07 11:18:51 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

static void	render_scene(t_window *window)
{
	t_vec2	coord;
	int	color;

	coord.y = 0;
	while (coord.y <= window->height)
	{
		coord.x = 0;
		while (coord.x <= window->width)
		{
			color = cast_ray(window, &coord);
			mlx_pixel_put(window->mlx_ptr, window->window,
				coord.x, coord.y, color);
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
	mlx_hook(window->window, 17, 1L << 0, quit_game, window);
	render_scene(window);
	mlx_loop(window->mlx_ptr);
	return ;
}
