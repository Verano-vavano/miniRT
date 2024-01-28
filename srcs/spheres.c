/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:52 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/28 07:03:53 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

// a = Dir²
// Dir normalized, hence x² + y² + z² = 1
// a = 1, so a isn't required
// This omission only works if Dir is normalized
static bool	sphere_intersect(t_sphere *sp, t_ray ray, double *hit)
{
	double	b, c, discr, x_hit1, x_hit2;
	t_vec3	sphere_org_rel;

	b = 2.0f * vec3_dot(sphere_org_rel, ray.dir);
	c = vec3_dot(sphere_org_rel, sphere_org_rel) - pow(sp->diameter / 2, 2);
	discr = pow(b, 2) - (4 * c);
	if (discr < 0)
		return (false);
	discr = sqrt(discr);
	x_hit1 = - (b + discr) / 2;
	x_hit2 = - (b - discr) / 2;
	if (x_hit1 >= 0 && (x_hit2 < 0 || x_hit1 < x_hit2))
		*hit = x_hit1;
	else if (x_hit2 >= 0 && (x_hit1 < 0 || x_hit2 < x_hit1))
		*hit = x_hit2;
	else
		return (false);
	return (true);
}

bool	sp_render(t_sphere *sp, t_ray r, double *x, t_lform *lform)
{
	double	hit_near, hit;
	t_sphere *closest;

	hit_near = INFINITY;
	closest = NULL;
	while (sp)
	{
		if (sphere_intersect(sp, r, &hit) && hit < hit_near)
		{
			hit_near = hit;
			closest = sp;
		}
		sp = sp->next_sphere;
	}
	if (closest)
	{
		*x = hit_near;
		if (lform)
		{
			lform->addr = (void *) closest;
			lform->shape = 's';
		}
	}
	return (closest != NULL);
}
