/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:26:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/10 21:49:53 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	light_pathing(t_scene *scene, t_vec3 normal)
{
	float	albedo = 1.f;
	float	d = (albedo / M_PI) * scene->light.lgt_ratio * fmax(0, vec3_dot(normal, scene->light.inv_dir));

	t_color	ret;
	ret.r = d * scene->light.color.r;
	ret.g = d * scene->light.color.g;
	ret.b = d * scene->light.color.b;
	return (ret);
}
