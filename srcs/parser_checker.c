/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:36:09 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/05 11:06:46 by hdupire          ###   ########.fr       */
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
		return (invalid_range_error("AMBIENT", "0.0", "1.0"));
	if (scene->ambient.color.valid == false)
		return (false);
	return (true);
}

bool	check_camera(t_scene *scene)
{
	if (scene->camera.vp.valid == false || scene->camera.dir.valid == false)
		return (false);
	else if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (invalid_range_error("CAMERA", "0", "180"));
	return (true);
}

bool	check_light(t_scene *scene)
{
	if (scene->light.lgt_ratio > 100000.0f)
		return (false);
	if (scene->light.lgt_ratio < 0.0f || scene->light.lgt_ratio > 1.0f)
		return (invalid_range_error("LIGHT", "0.0", "1.0"));
	if (scene->light.pos.valid == false || scene->light.color.valid == false)
		return (false);
	return (true);
}
