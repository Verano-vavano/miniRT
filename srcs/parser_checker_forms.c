/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker_forms.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:06:52 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/03 22:14:57 by hdupire          ###   ########.fr       */
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
		return (invalid_range_err("SPHERE", "0.0", "99999.9"));
	if (scene->last_sphere->pos.valid == false
		|| scene->last_sphere->color.valid == false)
		return (false);
	return (true);
}

bool	check_last_plane(t_scene *scene)
{
	t_plane	*p;

	p = scene->last_plane;
	if (!p->point.valid
		|| !p->normal.valid
		|| !p->color.valid)
		return (false);
	if (p->normal.z > 0)
		p->normal = vec3_mult_float(p->normal, -1.f);
	return (true);
}

bool	check_last_cyl(t_scene *scene)
{
	t_cylinder	*c;

	c = scene->last_cyl;
	if (c->diameter > 100000.0f || c->diameter < 0.f
		|| c->height > 100000.0f || c->height < 0.f)
		return (false);
	else if (!c->center.valid || !c->normal.valid
		|| !c->color.valid)
		return (false);
	if (c->normal.z > 0)
		c->normal = vec3_mult_float(c->normal, -1.f);
	return (true);
}
