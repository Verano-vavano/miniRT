/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_forms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:38:25 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/05 18:15:27 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "errors.h"
#include "libft.h"

bool	set_new_arg_sphere(t_scene *scene, char *arg, short arg_num)
{
	struct s_sphere	*new_sphere;

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
	else
		return (too_many_args_err("SPHERE", "3"));
	return (true);
}
