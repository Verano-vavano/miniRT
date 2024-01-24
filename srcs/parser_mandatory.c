/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mandatory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 00:18:52 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/23 21:08:44 by hdupire          ###   ########.fr       */
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

static bool	set_new_arg_light(t_scene *sc, char *arg, short arg_num, bool sph)
{
	t_light	*new_light;

	if (arg_num == 1)
	{
		new_light = ft_calloc(1, sizeof (struct s_light));
		if (!new_light)
			return (malloc_err("LIGHT"));
		if (sph)
		{
			if (!sc->lighting.s_light)
				sc->lighting.s_light = new_light;
			else
				sc->lighting.last_s_light->next_light = new_light;
			sc->lighting.last_s_light = new_light;
		}
		else
		{
			if (!sc->lighting.light)
				sc->lighting.light = new_light;
			else
				sc->lighting.last_light->next_light = new_light;
			sc->lighting.last_light = new_light;
		}
	}
	if (sph)
		new_light = sc->lighting.last_s_light;
	else
		new_light = sc->lighting.last_light;
	if (arg_num == 2)
		new_light->vec = get_coord_vec3(arg, false);
	else if (arg_num == 3)
		new_light->lgt_ratio = little_atof(arg);
	else if (arg_num == 4)
	{
		new_light->color = get_color(arg);
		return (check_light(new_light));
	}
	else if (arg_num == 5)
		return (too_many_args_err("LIGHT", "3"));
	return (true);
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
		if (name == CAMERA)
			ret = set_arg_camera(scene, arg, arg_num);
		else if (name == AMBIENT)
			ret = set_arg_ambient(scene, arg, arg_num);
		else if (name == DIR_LIGHT)
			ret = set_new_arg_light(scene, arg, arg_num, false);
		else if (name == SPH_LIGHT)
			ret = set_new_arg_light(scene, arg, arg_num, true);
		else if (name == SPHERE)
			ret = set_new_arg_sphere(scene, arg, arg_num);
		else if (name == PLANE)
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
