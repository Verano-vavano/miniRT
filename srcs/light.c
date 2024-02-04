/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:26:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 13:07:29 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	sph_lighting(t_scene *scene, t_hit *hit, t_col01 *ret)
{
	t_light	*s_light;
	t_vec3	light_dir;
	t_ray	new_ray;
	t_lform	temp;
	float	r;
	float	r2;
	float	d;

	s_light = scene->lighting.s_light;
	while (s_light)
	{
		temp.addr = NULL;
		light_dir = vec3_sub(s_light->vec, hit->hit);
		new_ray.org = vec3_add(hit->hit, vec3_mult_float(hit->normal, SHADOW_BIAS));
		r2 = light_dir.x * light_dir.x + light_dir.y * light_dir.y + light_dir.z * light_dir.z;
		r = sqrtf(r2);
		new_ray.dir = vec3_mult_float(light_dir, 1.f/r);
		t_hit t = trace(scene, new_ray, &temp, true);
		if (temp.addr == NULL || t.t > r + EPSILON)
		{
			d = s_light->lgt_ratio / (4 * M_PI * r2);
			ret->r = fmin(1.f, ret->r + hit->color.r * d * s_light->color.r);
			ret->g = fmin(1.f, ret->g + hit->color.g * d * s_light->color.g);
			ret->b = fmin(1.f, ret->b + hit->color.b * d * s_light->color.b);
		}
		s_light = s_light->next_light;
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
		new_ray.org = vec3_add(hit->hit, vec3_mult_float(hit->normal, SHADOW_BIAS));
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
