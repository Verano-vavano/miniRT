/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:40:01 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 00:14:46 by hdupire          ###   ########.fr       */
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

static bool	is_movement(int key, char k, t_window *window)
{
	t_vec3	*to_change;

	printf("%d\n", window->rmb_pressed);
	if (!window->rmb_pressed)
		to_change = &(window->scene->camera.vp);
	else
		to_change = &(window->scene->camera.dir);
	if ((key == 'z' && k == 'a') || (key == 'w' && k == 'q') || key == UP)
		to_change->z++;
	else if (key == 's' || key == DOWN)
		to_change->z--;
	else if ((key == 'a' && k == 'q') || (key == 'q' && k == 'a') || key == LEFT)
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

static void	size_modif(t_window *window, char key, t_lform lf)
{
	int	mod;

	mod = (1 * (key == 'p')) + (-1 * (key == 'm'));
	if (lf.shape == 's')
	{
		t_sphere	*sp = (t_sphere *) lf.addr;
		sp->diameter += mod;
	}
	else if (lf.shape == 'c')
	{
		t_cylinder	*cy = (t_cylinder *) lf.addr;
		if (window->height_mod)
			cy->height += mod;
		else
			cy->radius += mod;
	}
	else
		return ;
	render_scene(&window);
}

int	key_event(int key, t_window *window)
{
	if (key == ESCAPE)
		quit_game(window);
	else if (is_movement(key, window->keyboard, window))
		return (0);
	else if (key == 'l')
	{
		window->last_selected.addr = window->scene->lighting.movable;
		window->last_selected.shape = 'l';
	}
	else if (key == 'o')
		window->height_mod ^= true;
	else if (key == 'p' || key == 'm')
		size_modif(window, key, window->last_selected);
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
	else if (key == 'i' && window->transform.type != 'f')
		window->transform.temp *= -1;
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

	if (button == 3)
	{
		window->rmb_pressed ^= true;
		return (0);
	}
	coord.x = x;
	coord.y = y;
	calculate_ray(&ray, window, &coord, window->scene->camera.fov * M_PI / 180);
	trace(window->scene, ray, &(window->last_selected), true);
	if (window->last_selected.addr)
		printf("%c\n", window->last_selected.shape);
	return (0);
}
