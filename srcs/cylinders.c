/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:19:23 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 01:18:30 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	cyl_intersect(t_cylinder *cyl, t_ray ray, double *hit)
{
	double	a, b, c;
	t_vec3	x, d, v;
	double	dv, xv;

	d = ray.dir;
	v = cyl->normal;
	x = vec3_sub(ray.org, cyl->center);
	dv = vec3_dot(d, v);
	xv = vec3_dot(x, v);
	a = 1 - pow(dv, 2);
	b = 2 * (vec3_dot(d, x) - (dv * xv));
	c = fabs(vec3_dot(x, x) - pow(xv, 2) - pow(cyl->radius, 2));
	if (quadratic(a, b, c, hit))
	{
		t_vec3	point;
		point = vec3_add(ray.org, vec3_mult_float(ray.dir, *hit));
		return (!(point.x < cyl->center.x - cyl->height ||
			point.x > cyl->center.x + cyl->height ||
			point.y < cyl->center.y - cyl->height ||
			point.y > cyl->center.y + cyl->height ||
			point.z < cyl->center.z - cyl->height ||
			point.z > cyl->center.z + cyl->height));
	}
	return (false);
}

bool	cyl_render(t_cylinder *cyl, t_ray ray, double *x, t_lform *lform)
{
	double	hit_near, hit;
	t_cylinder *closest;

	hit_near = INFINITY;
	closest = NULL;
	while (cyl)
	{
		if (cyl_intersect(cyl, ray, &hit) && hit < hit_near)
		{
			hit_near = hit;
			closest = cyl;
		}
		cyl = cyl->next;
	}
	if (closest)
	{
		*x = hit_near;
		if (lform)
		{
			lform->addr = (void *) closest;
			lform->shape = 'c';
		}
	}
	return (closest != NULL);
}
