/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:40:01 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 18:24:38 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "keys.h"
#include "libft.h"

int	quit_game(t_window *window)
{
	mlx_destroy_window(window->mlx_ptr, window->window);
	free_scene(window->scene);
	free(window);
	exit(0);
}

int	unminimize(t_window *window)
{
	mlx_clear_window(window->mlx_ptr, window->window);
	mlx_put_image_to_window(window->mlx_ptr, window->window,
		window->img.img, 0, 0);
	return (0);
}

int	mousedown(int button, int x, int y, t_window *window)
{
	t_ray	ray;
	t_vec2	coord;

	if (button == 3)
	{
		printf("Rotate mode toggled (%d)\n", window->rmb_pressed);
		window->rmb_pressed ^= true;
		return (0);
	}
	coord.x = x;
	coord.y = y;
	calculate_ray(&ray, window, &coord, window->scene->camera.fov * M_PI / 180);
	trace(window->scene, ray, &(window->last_selected), true);
	if (window->last_selected.addr)
		printf("New form selected (%c)\n", window->last_selected.shape);
	return (0);
}
