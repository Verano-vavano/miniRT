/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:12:32 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/23 11:20:22 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	plane_intersect(struct s_plane *pl, t_vec3 org, t_vec3 dir, double *hit)
{
	double	denom;
	t_vec3	p010;

	denom = vec3_dot(pl->normal, dir);
	if (denom < 1e-6)
		return (false);
	p010 = vec3_sub(pl->point, org);
	*hit = vec3_dot(p010, pl->normal) / denom;
	if (*hit >= 0)
	{
		return (true);
	}
	return (false);
}

bool	planes_render_all(struct s_plane *pl, t_vec3 org, t_vec3 dir, double *x, t_color *closest_col)
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
		closest_col->r = closest->color.r;
		closest_col->g = closest->color.g;
		closest_col->b = closest->color.b;
	}
	return (closest != NULL);
}
