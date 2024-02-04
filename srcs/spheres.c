/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:52 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 19:57:32 by hdupire          ###   ########.fr       */
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
	double	b;
	double	c;
	t_vec3	sphere_org_rel;

	sphere_org_rel = vec3_sub(ray.org, sp->pos);
	b = 2.0f * vec3_dot(sphere_org_rel, ray.dir);
	c = vec3_dot(sphere_org_rel, sphere_org_rel) - pow(sp->diameter / 2, 2);
	return (quadratic(1, b, c, hit));
}

static void	sphere_assign_hit(t_hit *x, double hit_near, t_sphere *sp, t_ray r)
{
	x->t = hit_near;
	x->hit = calc_ray_point(r, x->t);
	x->normal = vec3_normalize(vec3_sub(x->hit, sp->pos));
	x->color = copy_col_to_01(sp->color);
	x->shade = &(sp->shading);
}

bool	sp_render(t_sphere *sp, t_ray r, t_hit *x, t_lform *lform)
{
	double		hit_near;
	double		hit;
	t_sphere	*closest;

	x->t = INFINITY;
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
	if (!closest)
		return (false);
	sphere_assign_hit(x, hit_near, closest, r);
	if (lform)
	{
		lform->addr = (void *) closest;
		lform->shape = 's';
	}
	return (true);
}
