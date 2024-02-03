/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:40:01 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/03 03:29:03 by hdupire          ###   ########.fr       */
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

int	key_event(int key, t_window *window)
{
	if (key == ESCAPE || key == 'p')
		quit_game(window);
	else if (key == 'z' || key == 'w' || key == UP)
	{
		window->scene->camera.vp.z++;
		render_scene(&window);
	}
	else if (key == 's' || key == DOWN)
	{
		window->scene->camera.vp.z--;
		render_scene(&window);
	}
	else if (key == 'a' || key == 'q' || key == LEFT)
	{
		window->scene->camera.vp.x--;
		render_scene(&window);
	}
	else if (key == 'd' || key == RIGHT)
	{
		window->scene->camera.vp.x++;
		render_scene(&window);
	}
	return (0);
}

int	mousedown(int button, int x, int y, t_window *window)
{
	t_ray	ray;
	t_vec2	coord;

	coord.x = x;
	coord.y = y;
	calculate_ray(&ray, window, &coord, window->scene->camera.fov * M_PI / 180);
	trace(window->scene, ray, &(window->last_selected), true);
	if (window->last_selected.addr)
		printf("%c\n", window->last_selected.shape);
	(void) button;
	return (0);
}
