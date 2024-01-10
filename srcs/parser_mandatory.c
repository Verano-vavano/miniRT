/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mandatory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 00:18:52 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/10 21:48:39 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "errors.h"
#include "libft.h"

static bool	set_arg_ambient(t_scene *scene, char *arg, short arg_num)
{
	if (arg_num == 2)
		scene->ambient.lgt_ratio = little_atof(arg);
	else if (arg_num == 3)
	{
		scene->ambient.color = get_color(arg);
		scene->has_ambient = true;
		return (check_ambient(scene));
	}
	else if (arg_num == 4)
		return (too_many_args_err("AMBIENT", "2"));
	return (true);
}

static bool	set_arg_camera(t_scene *scene, char *arg, short arg_num)
{
	if (arg_num == 1)
		scene->camera.fov = -1;
	else if (arg_num == 2)
		scene->camera.vp = get_coord_vec3(arg, false);
	else if (arg_num == 3)
		scene->camera.dir = get_coord_vec3(arg, true);
	else if (arg_num == 4 && is_intable(arg))
	{
		scene->camera.fov = ft_atoi(arg);
		scene->has_camera = true;
		return (check_camera(scene));
	}
	else if (arg_num == 5)
		return (too_many_args_err("CAMERA", "3"));
	return (true);
}

static bool	set_arg_light(t_scene *scene, char *arg, short arg_num)
{
	if (arg_num == 2)
		scene->light.dir = get_coord_vec3(arg, false);
	else if (arg_num == 3)
		scene->light.lgt_ratio = little_atof(arg);
	else if (arg_num == 4)
	{
		scene->light.color = get_color(arg);
		return (check_light(scene));
	}
	else if (arg_num == 5)
		return (too_many_args_err("LIGHT", "3"));
	return (true);
}

// RET = 1 : CONTINUE
// RET = 0 : ERROR
bool	adder(t_scene *scene, char *line, bool *verif, char name)
{
	int	advancement;
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
		if (name == 'C')
			ret = set_arg_camera(scene, arg, arg_num);
		else if (name == 'A')
			ret = set_arg_ambient(scene, arg, arg_num);
		else if (name == 'L')
			ret = set_arg_light(scene, arg, arg_num);
		else if (name == 's')
			ret = set_new_arg_sphere(scene, arg, arg_num);
		else if (name == 'p')
			ret = set_new_arg_plane(scene, arg, arg_num);
		free(arg);
		arg_num++;
		line += advancement;
		arg = get_line_arg(line, &advancement);
	}
	if (arg)
		free(arg);
	return (ret);
}
