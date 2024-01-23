/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:26:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/19 16:40:02 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	light_pathing(t_scene *scene, t_vec3 hit, t_vec3 normal, t_col01 *ret, t_col01 lf)
{
	float		albedo = 1.f;
	float		d;
	struct s_light	*light;
	t_lform		temp;

	light = scene->lighting.light;
	while (light)
	{
		temp.addr = NULL;
		trace(scene, vec3_add(hit, vec3_mult_float(normal, 0.9)), light->inv_dir, &temp);
		if (temp.addr == NULL)
		{
			d = (albedo / M_PI) * light->lgt_ratio * fmax(0, vec3_dot(normal, light->inv_dir));
			ret->r = fmin(1.f, ret->r + lf.r * d * light->color.r / 255.f);
			ret->g = fmin(1.f, ret->g + lf.g * d * light->color.g / 255.f);
			ret->b = fmin(1.f, ret->b + lf.b * d * light->color.b / 255.f);
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
