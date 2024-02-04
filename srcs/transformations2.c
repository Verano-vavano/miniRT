/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:24:41 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 15:52:23 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"
#include "keys.h"

static void	cyl_size_modif(t_window *window, t_lform lf, int mod)
{
	t_cylinder	*cy;
	long		new;

	cy = (t_cylinder *) lf.addr;
	if (window->height_mod)
		new = cy->height + mod;
	else
		new = cy->radius + mod;
	if (new >= 0 && new < INT_MAX)
	{
		if (window->height_mod)
			cy->height = new;
		else
			cy->radius = new;
	}
}

void	size_modif(t_window *window, char key, t_lform lf)
{
	t_sphere	*sp;
	int			mod;
	long		new;

	mod = (1 * (key == 'p')) + (-1 * (key == 'm'));
	if (lf.shape == 's')
	{
		sp = (t_sphere *) lf.addr;
		new = sp->diameter + mod;
		if (new >= 0 && new < INT_MAX)
			sp->diameter += mod;
	}
	else if (lf.shape == 'c')
		cyl_size_modif(window, lf, mod);
	else
		return ;
	render_scene(&window);
}

short	get_eq(int key)
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

