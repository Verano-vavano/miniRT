/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:36:09 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/12 17:28:21 by hdupire          ###   ########.fr       */
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

bool	check_light(t_scene *scene)
{
	struct s_light	*now;
	struct s_light	*next;

	now = scene->light;
	while (now)
	{
		next = now->next_light;
		if (now->lgt_ratio > 100000.0f)
			return (false);
		if (now->lgt_ratio < 0.0f || now->lgt_ratio > 1.0f)
			return (invalid_range_err("LIGHT", "0.0", "1.0"));
		if (now->dir.valid == false || now->color.valid == false)
			return (false);
		now->dir = vec3_normalize(now->dir);
		now->inv_dir = vec3_mult_float(now->dir, -1.f);
		now = next;
	}
	return (true);
}
