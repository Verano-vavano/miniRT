/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:54:15 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 18:01:23 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "errors.h"

static bool	adder_caller(t_scene *sc, char *arg, short arg_num, int name)
{
	if (name == CAMERA)
		return (set_arg_camera(sc, arg, arg_num));
	else if (name == AMBIENT)
		return (set_arg_ambient(sc, arg, arg_num));
	else if (name == DIR_LIGHT)
		return (set_new_arg_light(sc, arg, arg_num, false));
	else if (name == SPH_LIGHT)
		return (set_new_arg_light(sc, arg, arg_num, true));
	else if (name == SPHERE)
		return (set_new_arg_sphere(sc, arg, arg_num));
	else if (name == PLANE)
		return (set_new_arg_plane(sc, arg, arg_num));
	else if (name == CYLINDER)
		return (set_new_arg_cyl(sc, arg, arg_num));
	return (false);
}

// RET = 1 : CONTINUE
// RET = 0 : ERROR
bool	adder(t_scene *scene, char *line, bool *verif, enum e_scene_arg name)
{
	int		advancement;
	short	arg_num;
	char	*arg;
	short	ret;

	if (verif && *verif)
		return (already_set_err(name));
	arg = get_line_arg(line, &advancement);
	arg_num = 1;
	ret = true;
	while (arg && ret)
	{
		ret = adder_caller(scene, arg, arg_num, name);
		free(arg);
		arg_num++;
		line += advancement;
		arg = get_line_arg(line, &advancement);
	}
	if (arg)
		free(arg);
	return (ret);
}
