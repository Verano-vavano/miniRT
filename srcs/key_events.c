/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:43:58 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 19:49:42 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "keys.h"
#include "libft.h"

static bool	is_movement(int key, char k, t_window *window)
{
	t_vec3	*to_change;

	if (!window->rmb_pressed)
		to_change = &(window->scene->camera.vp);
	else
		to_change = &(window->scene->camera.dir);
	if ((key == 'z' && k == 'a') || (key == 'w' && k == 'q') || key == UP)
		to_change->z++;
	else if (key == 's' || key == DOWN)
		to_change->z--;
	else if ((key == 'a' && k == 'q') || (key == 'q' && k == 'a')
		|| key == LEFT)
		to_change->x--;
	else if (key == 'd' || key == RIGHT)
		to_change->x++;
	else if ((key == 'a' && k == 'a') || (key == 'q' && k == 'q'))
		to_change->y--;
	else if (key == 'e')
		to_change->y++;
	else
		return (false);
	if (window->rmb_pressed)
		lookat(window);
	render_scene(&window);
	return (true);
}

static void	rescue_funk(int key, t_window *window)
{
	if (key == 'v')
		window->transform.x = window->transform.temp;
	else if (key == 'b')
		window->transform.y = window->transform.temp;
	else if (key == 'n')
		window->transform.z = window->transform.temp;
	window->transform.temp = 0;
	printf("Current transformation : (%d, %d, %d)\n",
		window->transform.x, window->transform.y, window->transform.z);
}

static bool	transfo_key_events(int key, t_window *window)
{
	if (key == 'r' || key == 't' || key == 'f')
	{
		printf("Transform mode toggled (%c)\n", key);
		window->transform.type = key;
		window->transform.temp = 0;
	}
	else if (key == 'v' || key == 'b' || key == 'n')
		rescue_funk(key, window);
	else if (key == SPACE)
	{
		printf("Transformation applied ! :)\n");
		apply_transformation(window->last_selected, window->transform);
		render_scene(&window);
	}
	else if (key == 'i' && window->transform.type != 'f')
	{
		window->transform.temp *= -1;
		printf("| (%d)\n", window->transform.temp);
	}
	else
		return (false);
	return (true);
}

static void	transfo_add_val(t_window *window, int key)
{
	short	n;

	window->transform.temp *= 10;
	if (window->keyboard == 'a')
		n = get_eq(key);
	else
		n = key - '0';
	printf("| %d (%d)\n", n, window->transform.temp);
	window->transform.temp += n;
	if (window->transform.temp > 999)
	{
		printf("Too high value !\n");
		window->transform.temp = 0;
	}
}

int	key_event(int key, t_window *window)
{
	if (key == ESCAPE)
		quit_game(window);
	else if (is_movement(key, window->keyboard, window))
		return (0);
	else if (key == 'l' && window->scene->lighting.movable)
	{
		printf("Movable light selected\n");
		window->last_selected.addr = window->scene->lighting.movable;
		window->last_selected.shape = 'l';
	}
	else if (key == 'o')
	{
		window->height_mod ^= true;
		printf("Height mode toggled (%d)\n", window->height_mod);
	}
	else if (key == 'p' || key == 'm')
		size_modif(window, key, window->last_selected);
	else if (transfo_key_events(key, window))
		return (0);
	else if (window->transform.type != 'f')
		transfo_add_val(window, key);
	return (0);
}
