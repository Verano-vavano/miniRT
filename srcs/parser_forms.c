/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_forms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:38:25 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 14:31:59 by hdupire          ###   ########.fr       */
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
	else if (!set_shade(&(scene->last_sphere->shading), arg))
		too_many_args_war("SPHERE", "3");
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
	else if (!set_shade(&(scene->last_plane->shading), arg))
		too_many_args_war("PLANE", "3");
	return (true);
}

static bool	create_new_cyl(t_scene *scene)
{
	t_cylinder	*new_cyl;

	new_cyl = ft_calloc(1, sizeof (t_cylinder));
	if (!new_cyl)
		return (malloc_err("CYLINDER"));
	if (!scene->cyl)
		scene->cyl = new_cyl;
	else
		scene->last_cyl->next = new_cyl;
	scene->last_cyl = new_cyl;
	return (true);
}

bool	set_new_arg_cyl(t_scene *scene, char *arg, short arg_num)
{
	if (arg_num == 1)
		return (create_new_cyl(scene));
	else if (arg_num == 2)
		scene->last_cyl->center = get_coord_vec3(arg, false);
	else if (arg_num == 3)
		scene->last_cyl->dir = vec3_normalize(get_coord_vec3(arg, false));
	else if (arg_num == 4)
		scene->last_cyl->diameter = little_atof(arg);
	else if (arg_num == 5)
		scene->last_cyl->height = little_atof(arg);
	else if (arg_num == 6)
	{
		scene->last_cyl->color = get_color(arg);
		return (check_last_cyl(scene));
	}
	else if (!set_shade(&(scene->last_cyl->shading), arg))
		too_many_args_war("CYLINDER", "5");
	return (true);
}
