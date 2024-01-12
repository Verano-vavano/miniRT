/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:26:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/12 16:32:22 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	light_pathing(t_scene *scene, t_vec3 normal, t_col01 *ret, t_col01 lf)
{
	float	albedo = 1.f;
	float	d = (albedo / M_PI) * scene->light.lgt_ratio * fmax(0, vec3_dot(normal, scene->light.inv_dir));

	ret->r = lf.r * d * scene->light.color.r / 255.f;
	ret->g = lf.g * d * scene->light.color.g / 255.f;
	ret->b = lf.b * d * scene->light.color.b / 255.f;
}

void	ambient_lighting(struct s_ambient amb, t_col01 *ret, t_col01 lf)
{
	ret->r = fmin(1.f, lf.r * amb.lgt_ratio * (amb.color.r / 255.f));
	ret->g = fmin(1.f, lf.g * amb.lgt_ratio * (amb.color.g / 255.f));
	ret->b = fmin(1.f, lf.b * amb.lgt_ratio * (amb.color.b / 255.f));
}
