/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker_forms.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:06:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/05 15:27:12 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "errors.h"
#include "libft.h"

bool	check_last_sphere(t_scene *scene)
{
	if (scene->last_sphere->diameter > 100000.0f)
		return (false);
	if (scene->last_sphere->diameter < 0.0f)
		return (invalid_range_error("SPHERE", "0.0", "99999.9"));
	if (scene->last_sphere->pos.valid == false
		|| scene->last_sphere->color.valid == false)
		return (false);
	return (true);
}
