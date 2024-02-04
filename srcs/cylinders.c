/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:19:23 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 14:27:14 by hdupire          ###   ########.fr       */
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

static bool	check_cyl_center(t_cylinder *cyl, t_ray ray, t_hit *hit)
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
	if (t < hit->t)
	{
		hit->t = t;
		return (true);
	}
	return (false);
}

static bool	check_cyl_planes(t_plane *p, t_ray ray, t_hit *hit, float radius)
{
	double	tmp_hit;
	t_vec3	col;

	if (plane_intersect(p, ray, &tmp_hit))
	{
		col = calc_ray_point(ray, tmp_hit);
		if (vec3_dist(col, p->point) < radius && tmp_hit < hit->t)
		{
			hit->t = tmp_hit;
			return (true);
		}
	}
	return (false);
}

static void	calculate_cyl_normal(t_cylinder *cyl, t_hit *hit, bool is_plane)
{
	double	h;

	if (is_plane)
		copy_2vec3(&(hit->normal), cyl->dir);
	else
	{
		h = vec3_dot(vec3_sub(hit->hit, cyl->center), cyl->dir);
		hit->normal = vec3_normalize(vec3_sub(hit->hit, vec3_add(cyl->center, vec3_mult_float(cyl->dir, h))));
	}
}

static bool	cyl_intersect(t_cylinder *cyl, t_ray ray, t_hit *hit)
{
	t_plane	extremities;
	bool	new_hit;
	bool	is_plane;

	hit->t = INFINITY;
	new_hit = false;
	extremities.normal = cyl->dir;
	extremities.point = cyl->p_bot;
	new_hit |= check_cyl_planes(&extremities, ray, hit, cyl->radius);
	extremities.point = cyl->p_top;
	new_hit |= check_cyl_planes(&extremities, ray, hit, cyl->radius);
	is_plane = new_hit;
	if (check_cyl_center(cyl, ray, hit))
	{
		is_plane = false;
		new_hit = true;
	}
	if (new_hit)
	{
		hit->hit = calc_ray_point(ray, hit->t);
		calculate_cyl_normal(cyl, hit, is_plane);
	}
	return (new_hit);
}

bool	cyl_render(t_cylinder *cyl, t_ray ray, t_hit *x, t_lform *lform)
{
	t_hit	hit_near, hit;
	t_cylinder *closest;

	hit_near.t = INFINITY;
	closest = NULL;
	while (cyl)
	{
		if (cyl_intersect(cyl, ray, &hit) && hit.t < hit_near.t)
		{
			hit_near = hit;
			closest = cyl;
		}
		cyl = cyl->next;
	}
	if (closest)
	{
		x->t = hit_near.t;
		x->hit = hit_near.hit;
		x->normal = hit_near.normal;
		x->color = copy_col_to_01(closest->color);
		x->shade = &(closest->shading);
		if (lform)
		{
			lform->addr = (void *) closest;
			lform->shape = 'c';
		}
	}
	return (closest != NULL);
}
