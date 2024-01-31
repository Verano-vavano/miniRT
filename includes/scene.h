/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:10:56 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/31 09:55:12 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "main.h"
# include "render.h"

# include <fcntl.h>

// SCENE
t_scene	*get_scene(char *file);

// SCENES UTILS
char	*get_line_arg(char *line, int *adv);

void	free_scene(t_scene *scene);

// PARSER
bool	adder(t_scene *scene, char *line, bool *verif, enum e_scene_arg name);

// PARSER FORMS
bool	set_new_arg_sphere(t_scene *scene, char *arg, short arg_num);
bool	set_new_arg_plane(t_scene *scene, char *arg, short arg_num);
bool	set_new_arg_cyl(t_scene *scene, char *arg, short arg_num);

// CHECKER
bool	check_ambient(t_scene *scene);
bool	check_camera(t_scene *scene);
bool	check_light(struct s_light *light);
bool	check_last_sphere(t_scene *scene);
bool	check_last_plane(t_scene *scene);
bool	check_last_cyl(t_scene *scene);

// ATOF
float	little_atof(char *arg);

// COLORS
t_color	get_color(char *arg);

// VEC3
t_vec3	get_coord_vec3(char *arg, bool smallest);

#endif
