/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:36:09 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/19 17:57:50 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "errors.h"

bool	check_ambient(t_scene *scene)
{
	if (scene->ambient.lgt_ratio > 100000.0f)
		return (false);
	if (scene->ambient.lgt_ratio < 0.0f
		|| scene->ambient.lgt_ratio > 1.0f)
		return (invalid_range_err("AMBIENT", "0.0", "1.0"));
	if (scene->ambient.color.valid == false)
		return (false);
	return (true);
}

bool	check_camera(t_scene *scene)
{
	if (scene->camera.vp.valid == false || scene->camera.dir.valid == false)
		return (false);
	else if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (invalid_range_err("CAMERA", "0", "180"));
	return (true);
}

bool	check_light(struct s_light *light)
{
	if (light->lgt_ratio > 100000.0f)
		return (false);
	if (light->lgt_ratio < 0.0f || light->lgt_ratio > 1.0f)
		return (invalid_range_err("LIGHT", "0.0", "1.0"));
	if (light->vec.valid == false || light->color.valid == false)
		return (false);
	light->vec = vec3_normalize(light->vec);
	light->inv_dir = vec3_mult_float(light->vec, -1.f);
	return (true);
}
