/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:26:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/24 02:30:40 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	sph_lighting(t_scene *scene, t_vec3 hit, t_col01 *r, t_lform *lf)
{
	t_light	*s_light;
	t_vec3	light_dir;
	float	r2;
	float	d;

	s_light = scene->lighting.s_light;
	while (s_light)
	{
		light_dir = vec3_sub(s_light->vec, hit);
		r2 = vec3_length(light_dir);
		d = s_light->lgt_ratio / (4 * M_PI * r2);
		r->r = fmin(1.f, r->r + lf->color.r * d * s_light->color.r / 255.f);
		r->g = fmin(1.f, r->g + lf->color.g * d * s_light->color.g / 255.f);
		r->b = fmin(1.f, r->b + lf->color.b * d * s_light->color.b / 255.f);
		s_light = s_light->next_light;
	}
}

void	dir_lighting(t_scene *scene, t_vec3 hit, t_col01 *r, t_lform *lf)
{
	float	d;
	t_light	*light;
	t_lform	temp;
	t_ray	new_ray;

	light = scene->lighting.light;
	while (light)
	{
		temp.addr = NULL;
		new_ray.org = vec3_add(hit, vec3_mult_float(lf->normal, SHADOW_BIAS));
		new_ray.dir = light->inv_dir;
		trace(scene, new_ray, &temp);
		if (temp.addr == NULL || (temp.shape == 'p' && !PLANE_SHADOW))
		{
			d = light->lgt_ratio * fmax(0,
					vec3_dot(lf->normal, light->inv_dir));
			r->r = fmin(1.f, r->r + lf->color.r * d * light->color.r / 255.f);
			r->g = fmin(1.f, r->g + lf->color.g * d * light->color.g / 255.f);
			r->b = fmin(1.f, r->b + lf->color.b * d * light->color.b / 255.f);
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
