/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_check_inter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:15:20 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 15:15:34 by hdupire          ###   ########.fr       */
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

bool	check_cyl_center(t_cylinder *cyl, t_ray ray, t_hit *hit)
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
	if (t >= hit->t)
		return (false);
	hit->t = t;
	return (true);
}

bool	check_cyl_planes(t_plane *p, t_ray ray, t_hit *hit, float radius)
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
