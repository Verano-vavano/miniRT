/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:19:23 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/05 11:54:53 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	calculate_cyl_normal(t_cylinder *cyl, t_hit *hit, bool is_plane)
{
	t_vec3	v;

	if (is_plane)
		copy_2vec3(&(hit->normal), cyl->dir);
	else
	{
		v = vec3_sub(cyl->center, hit->hit);
		hit->normal = vec3_cross(v, cyl->dir);
		hit->normal = vec3_normalize(vec3_cross(hit->normal, cyl->dir));
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

static void	cyl_get_hit_infos(t_hit *x, t_hit hit_near, t_cylinder *closest)
{
	x->t = hit_near.t;
	x->hit = hit_near.hit;
	x->normal = hit_near.normal;
	x->color = copy_col_to_01(closest->color);
	x->shade = &(closest->shading);
}

bool	cyl_render(t_cylinder *cyl, t_ray ray, t_hit *x, t_lform *lform)
{
	t_hit		hit_near;
	t_hit		hit;
	t_cylinder	*closest;

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
		cyl_get_hit_infos(x, hit_near, closest);
		if (lform)
		{
			lform->addr = (void *) closest;
			lform->shape = 'c';
		}
	}
	return (closest != NULL);
}
