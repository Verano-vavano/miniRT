/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/23 17:03:59 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

static bool	sphere_intersect(struct s_sphere *sp, t_vec3 org, t_vec3 dir, double *hit)
{
	double	a, b, c, discr, q, x_hit1, x_hit2;
	t_vec3	sphere_org_rel;

	sphere_org_rel = vec3_sub(org, sp->pos);
	a = vec3_dot(dir, dir);
	b = 2.0f * vec3_dot(sphere_org_rel, dir);
	c = vec3_dot(sphere_org_rel, sphere_org_rel) - pow(sp->diameter / 2, 2);
	discr = pow(b, 2) - (4 * a * c);
	if (discr < 0)
		return (false);
	if (b >= 0)
		q = -(b + discr) / 2;
	else
		q = -(b - discr) / 2;
	x_hit1 = q / a;
	x_hit2 = c / q;
	if (x_hit1 >= 0 && (x_hit2 < 0 || x_hit1 < x_hit2))
		*hit = x_hit1;
	else if (x_hit2 >= 0 && (x_hit1 < 0 || x_hit2 < x_hit1))
		*hit = x_hit2;
	else
		return (false);
	return (true);
}

bool	spheres_render_all(struct s_sphere *sp, t_vec3 org, t_vec3 dir, double *x, t_lform *lform)
{
	double	hit_near, hit;
	struct s_sphere *closest;

	hit_near = INFINITY;
	closest = NULL;
	while (sp)
	{
		if (sphere_intersect(sp, org, dir, &hit) && hit < hit_near)
		{
			hit_near = hit;
			closest = sp;
		}
		sp = sp->next_sphere;
	}
	if (closest)
	{
		*x = hit_near;
		lform->addr = (void *) closest;
		lform->shape = 's';
	}
	return (closest != NULL);
}
