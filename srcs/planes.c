/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:12:32 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 20:18:17 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	plane_intersect(t_plane *pl, t_ray ray, double *hit)
{
	float	d;
	float	denom;

	d = -vec3_dot(pl->normal, pl->point);
	denom = vec3_dot(pl->normal, ray.dir);
	if (fabs(denom) < 1e-6)
		return (false);
	*hit = - (vec3_dot(pl->normal, ray.org) + d) / denom;
	return (*hit > 0);
}

static void	pl_assign_hit(t_hit *x, t_plane *pl, t_ray ray)
{
	x->hit = calc_ray_point(ray, x->t);
	x->normal = pl->normal;
	x->color = copy_col_to_01(pl->color);
	x->shade = &(pl->shading);
}

bool	pl_render(t_plane *pl, t_ray ray, t_hit *x, t_lform *lform)
{
	double	hit;
	t_plane	*closest;

	x->t = INFINITY;
	closest = NULL;
	while (pl)
	{
		if (plane_intersect(pl, ray, &hit) && hit < x->t)
		{
			x->t = hit;
			closest = pl;
		}
		pl = pl->next_plane;
	}
	if (!closest)
		return (false);
	pl_assign_hit(x, closest, ray);
	if (lform)
	{
		lform->addr = (void *) closest;
		lform->shape = 'p';
	}
	return (true);
}
