/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:12:32 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/10 20:44:07 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	plane_intersect(struct s_plane *pl, t_vec3 org, t_vec3 dir, double *hit)
{
	double	denom;
	t_vec3	p0o;

	denom = vec3_dot(pl->normal, dir);
	if (denom < 1e-6)
		return (false);
	p0o = vec3_sub(pl->point, org);
	*hit = vec3_dot(p0o, pl->normal) / denom;
	if (*hit >= 0)
	{
		return (true);
	}
	return (false);
}

bool	planes_render_all(struct s_plane *pl, t_vec3 org, t_vec3 dir, double *x, t_lform *lform)
{
	double	hit_near, hit;
	struct s_plane *closest;

	hit_near = INFINITY;
	closest = NULL;
	while (pl)
	{
		if (plane_intersect(pl, org, dir, &hit) && hit < hit_near)
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
