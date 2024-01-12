/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:26:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/12 16:06:44 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	light_pathing(t_scene *scene, t_vec3 normal, t_col01 *ret)
{
	float	albedo = 1.f;
	float	d = (albedo / M_PI) * scene->light.lgt_ratio * fmax(0, vec3_dot(normal, scene->light.inv_dir));

	ret->r *= d * scene->light.color.r / 255.f;
	ret->g *= d * scene->light.color.g / 255.f;
	ret->b *= d * scene->light.color.b / 255.f;
}
