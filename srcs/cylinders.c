/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:19:23 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 12:21:16 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	intersect_tube_quadratic(t_cylinder *c, t_ray *ray, double abc[3])
{
	t_vec3	ray_x_tube;
	t_vec3	dif_x_dir;

	ray_x_tube = vec3_cross(ray->dir, c->dir);
	abc[0] = vec3_dot(ray_x_tube, ray_x_tube);
	dif_x_dir = vec3_cross(vec3_sub(ray->org, c->center), c->dir);
	abc[1] = 2.0 * vec3_dot(ray_x_tube, dif_x_dir);
	abc[2] = vec3_dot(dif_x_dir, dif_x_dir) - c->radius * c->radius;
}

static inline t_vec3	vec3_lin_comb(double alpha, t_vec3 a, double beta, t_vec3 b)
{
	return (vec3_add(vec3_mult_float(a, alpha), vec3_mult_float(b, beta)));
}

static bool	check_cyl_center(t_cylinder *cyl, t_ray ray, double *hit)
{
	double	abc[3];
	double	d;
	double	h;
	double	t;

	intersect_tube_quadratic(cyl, &ray, abc);
	d = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (d < 0 || abc[0] < 1e-6)
		return (-1.0);
	d = sqrt(d);
	t = (-abc[1] - d) / (2.0 * abc[0]);
	h = vec3_dot(vec3_sub(vec3_lin_comb(
					1.0, ray.org, t, ray.dir), cyl->center), cyl->dir);
	if (t < NEAR_CLIP || t > FAR_CLIP || fabs(h) > cyl->height / 2.0)
	{
		t = (-abc[1] + d) / (2.0 * abc[0]);
		h = vec3_dot(vec3_sub(vec3_lin_comb(
						1.0, ray.org, t, ray.dir), cyl->center), cyl->dir);
		if (t < NEAR_CLIP || t > FAR_CLIP || fabs(h) > cyl->height / 2.0)
			return (false);
	}
	if (t < *hit)
		*hit = t;
	return (true);
}

static bool	check_cyl_planes(t_plane *p, t_ray ray, double *hit, float radius)
{
	double	tmp_hit;
	t_vec3	col;

	if (plane_intersect(p, ray, &tmp_hit))
	{
		col = calc_ray_point(ray, tmp_hit);
		if (vec3_dist(col, p->point) < radius && tmp_hit < *hit)
		{
			*hit = tmp_hit;
			return (true);
		}
	}
	return (false);
}

static bool	cyl_intersect(t_cylinder *cyl, t_ray ray, double *hit)
{
	t_plane	extremities;
	bool	new_hit;

	*hit = INFINITY;
	new_hit = false;
	extremities.normal = cyl->dir;
	extremities.point = cyl->p_bot;
	new_hit |= check_cyl_planes(&extremities, ray, hit, cyl->radius);
	extremities.point = cyl->p_top;
	new_hit |= check_cyl_planes(&extremities, ray, hit, cyl->radius);
	new_hit |= check_cyl_center(cyl, ray, hit);
	return (new_hit);
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
