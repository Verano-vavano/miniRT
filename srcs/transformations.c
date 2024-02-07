/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:48:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 19:42:14 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rotation.h"

static void	sphere_transform(t_sphere *sp, t_transform t)
{
	if (t.type == 'r')
		return ;
	sp->pos.x += t.x;
	sp->pos.y += t.y;
	sp->pos.z += t.z;
}

static void	planes_transform(t_plane *pl, t_transform t)
{
	if (t.type == 't')
	{
		pl->point.x += t.x;
		pl->point.y += t.y;
		pl->point.z += t.z;
	}
	else if (t.type == 'r')
		apply_rotation(&(pl->normal), to_rad(t.x), to_rad(t.y), to_rad(t.z));
}

static void	cylinders_transform(t_cylinder *cl, t_transform t)
{
	if (t.type == 't')
	{
		cl->center.x += t.x;
		cl->center.y += t.y;
		cl->center.z += t.z;
	}
	else if (t.type == 'r')
		apply_rotation(&(cl->dir), to_rad(t.x), to_rad(t.y), to_rad(t.z));
    cl->p_bot = vec3_mult_float(cl->dir, cl->height * (-0.5));
    cl->p_top = vec3_mult_float(cl->dir, cl->height * 0.5);
    cl->p_bot = vec3_add(cl->p_bot, cl->center);
    cl->p_top = vec3_add(cl->p_top, cl->center);
    cl->radius = cl->diameter / 2.f;
}

static void	light_transform(t_light *l, t_transform t)
{
	if (t.type == 'r')
		return ;
	l->vec.x += t.x;
	l->vec.y += t.y;
	l->vec.z += t.z;
	if (!l->spherical)
    {
		l->vec = vec3_normalize(l->vec);
        l->inv_dir = vec3_mult_float(l->vec, -1.f);
    }
}

void	apply_transformation(t_lform select, t_transform transform)
{
	if (select.shape == 's')
		sphere_transform((t_sphere *) select.addr, transform);
	else if (select.shape == 'p')
		planes_transform((t_plane *) select.addr, transform);
	else if (select.shape == 'c')
		cylinders_transform((t_cylinder *) select.addr, transform);
	else if (select.shape == 'l' && select.addr)
		light_transform((t_light *) select.addr, transform);
}
