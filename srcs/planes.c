/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:12:32 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/23 20:40:12 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	plane_intersect(t_plane *pl, t_ray ray, double *hit)
{
	float	d;
	float	denom;

	d = -vec3_dot(pl->normal, pl->point);
	denom = vec3_dot(pl->normal, ray.dir);
	if (fabs(denom) < 1e-6)
		return (false);
	*hit = - (vec3_dot(pl->normal, ray.org) + d) / denom;
	return (*hit >= 0);
}

bool	pl_render(t_plane *pl, t_ray ray, double *x, t_lform *lform)
{
	double	hit_near, hit;
	t_plane *closest;

	hit_near = INFINITY;
	closest = NULL;
	while (pl)
	{
		if (plane_intersect(pl, ray, &hit) && hit < hit_near)
		{
			hit_near = hit;
			closest = pl;
		}
		pl = pl->next_plane;
	}
	if (closest)
	{
		*x = hit_near;
		if (lform)
		{
			lform->addr = (void *) closest;
			lform->shape = 'p';
		}
	}
	return (closest != NULL);
}
