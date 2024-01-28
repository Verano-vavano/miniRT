/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_forms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:38:25 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/28 06:38:10 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "errors.h"
#include "libft.h"

static bool	set_shade(t_shade *shade, char *arg)
{
	if (arg[0] == 'M')
		shade->reflect = true;
	else
		return (false);
	return (true);
}

bool	set_new_arg_sphere(t_scene *scene, char *arg, short arg_num)
{
	t_sphere	*new_sphere;

	if (arg_num == 1)
	{
		new_sphere = ft_calloc(1, sizeof (struct s_sphere));
		if (!new_sphere)
			return (malloc_err("SPHERE"));
		if (!scene->spheres)
			scene->spheres = new_sphere;
		else
			scene->last_sphere->next_sphere = new_sphere;
		scene->last_sphere = new_sphere;
	}
	else if (arg_num == 2)
		scene->last_sphere->pos = get_coord_vec3(arg, false);
	else if (arg_num == 3)
		scene->last_sphere->diameter = little_atof(arg);
	else if (arg_num == 4)
	{
		scene->last_sphere->color = get_color(arg);
		return (check_last_sphere(scene));
	}
	else if (set_shade(&(scene->last_sphere->shading), arg))
		return (true);
	else
		return (too_many_args_err("SPHERE", "3"));
	return (true);
}

bool	set_new_arg_plane(t_scene *scene, char *arg, short arg_num)
{
	t_plane	*new_plane;

	if (arg_num == 1)
	{
		new_plane = ft_calloc(1, sizeof (struct s_plane));
		if (!new_plane)
			return (malloc_err("PLANE"));
		if (!scene->planes)
			scene->planes = new_plane;
		else
			scene->last_plane->next_plane = new_plane;
		scene->last_plane = new_plane;
	}
	else if (arg_num == 2)
		scene->last_plane->point = get_coord_vec3(arg, false);
	else if (arg_num == 3)
		scene->last_plane->normal = vec3_normalize(get_coord_vec3(arg, false));
	else if (arg_num == 4)
	{
		scene->last_plane->color = get_color(arg);
		return (check_last_plane(scene));
	}
	else
		return (too_many_args_err("PLANE", "3"));
	return (true);
}
