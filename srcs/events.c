/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:40:01 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/03 04:01:08 by hdupire          ###   ########.fr       */
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

static short	get_eq(int key)
{
	if (key == ZERO)
		return (0);
	else if (key == ONE)
		return (1);
	else if (key == TWO)
		return (2);
	else if (key == THREE)
		return (3);
	else if (key == FOUR)
		return (4);
	else if (key == FIVE)
		return (5);
	else if (key == SIX)
		return (6);
	else if (key == SEVEN)
		return (7);
	else if (key == EIGHT)
		return (8);
	else if (key == NINE)
		return (9);
	return (0);
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
	else if (key == 'r' || key == 't' || key == 'f')
	{
		window->transform.type = key;
		printf("%c : transform start\n", key);
		window->transform.x = 0;
		window->transform.y = 0;
		window->transform.z = 0;
		window->transform.temp = 0;
	}
	else if (key == 'v' || key == 'b' || key == 'n')
	{
		if (key == 'v')
		{
			window->transform.x = window->transform.temp;
			printf("X : %d\n", window->transform.temp);
		}
		else if (key == 'b')
		{
			window->transform.y = window->transform.temp;
			printf("Y : %d\n", window->transform.temp);
		}
		if (key == 'n')
		{
			window->transform.z = window->transform.temp;
			printf("Z : %d\n", window->transform.temp);
		}
		window->transform.temp = 0;
	}
	else if (key == SPACE)
	{
		apply_transformation(window->last_selected, window->transform);
		render_scene(&window);
	}
	else if (window->transform.type != 'f')
	{
		window->transform.temp *= 10;
		short	n = get_eq(key);
		window->transform.temp += n;
		if (window->transform.temp > 999)
		{
			printf("Too high value !\n");
			window->transform.temp = 0;
		}
	}
	else
		printf("Key %d unknown\n", key);
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
