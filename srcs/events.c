/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:40:01 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/23 20:58:40 by hdupire          ###   ########.fr       */
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
