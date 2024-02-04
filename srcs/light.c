/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:26:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 17:40:00 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	sph_lgt_vals(t_light *sl, t_hit *hit, float rv[3], t_ray *nr)
{
	t_vec3	light_dir;

	light_dir = vec3_sub(sl->vec, hit->hit);
	nr->org = vec3_add(hit->hit, vec3_mult_float(hit->normal, SHADOW_BIAS));
	rv[0] = light_dir.x * light_dir.x + light_dir.y * light_dir.y
		+ light_dir.z * light_dir.z;
	rv[1] = sqrtf(rv[0]);
	nr->dir = vec3_normalize(vec3_mult_float(light_dir, 1.f / rv[1]));
}

void	sph_lighting(t_scene *scene, t_hit *hit, t_col01 *ret)
{
	t_light	*s_lgt;
	t_ray	new_ray;
	t_lform	temp;
	t_hit	t;
	float	rv[3];

	s_lgt = scene->lighting.s_light;
	while (s_lgt)
	{
		temp.addr = NULL;
		sph_lgt_vals(s_lgt, hit, rv, &new_ray);
		t = trace(scene, new_ray, &temp, true);
		if (temp.addr == NULL
			|| vec3_length(calc_ray_point(new_ray, t.t)) > rv[1] + EPSILON)
		{
			rv[2] = s_lgt->lgt_ratio / (4 * M_PI * rv[0]) * 0.3;
			ret->r = fmin(1.f, ret->r + hit->color.r * rv[2] * s_lgt->color.r);
			ret->g = fmin(1.f, ret->g + hit->color.g * rv[2] * s_lgt->color.g);
			ret->b = fmin(1.f, ret->b + hit->color.b * rv[2] * s_lgt->color.b);
		}
		s_lgt = s_lgt->next_light;
	}
}

void	dir_lighting(t_scene *scene, t_hit *hit, t_col01 *r)
{
	float	d;
	t_light	*light;
	t_lform	temp;
	t_ray	new_ray;

	light = scene->lighting.light;
	while (light)
	{
		temp.addr = NULL;
		new_ray.org = vec3_add(hit->hit,
				vec3_mult_float(hit->normal, SHADOW_BIAS));
		new_ray.dir = light->inv_dir;
		trace(scene, new_ray, &temp, PLANE_SHADOW == true);
		if (temp.addr == NULL)
		{
			d = light->lgt_ratio * fmax(0,
					vec3_dot(hit->normal, light->inv_dir));
			r->r = fmin(1.f, r->r + hit->color.r * d * light->color.r / 255.f);
			r->g = fmin(1.f, r->g + hit->color.g * d * light->color.g / 255.f);
			r->b = fmin(1.f, r->b + hit->color.b * d * light->color.b / 255.f);
		}
		light = light->next_light;
	}
}

void	ambient_lighting(struct s_ambient amb, t_col01 *ret, t_col01 lf)
{
	ret->r = fmin(1.f, lf.r * amb.lgt_ratio * (amb.color.r / 255.f));
	ret->g = fmin(1.f, lf.g * amb.lgt_ratio * (amb.color.g / 255.f));
	ret->b = fmin(1.f, lf.b * amb.lgt_ratio * (amb.color.b / 255.f));
}
