/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 05:20:29 by hdupire           #+#    #+#             */
/*   Updated: 2023/11/26 05:22:36 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_scene	*get_scene(char *file)
{
	t_scene	*scene;

	(void) file;
	scene = malloc(sizeof (t_scene));
	if (!scene)
		return (NULL);
	scene->is_valid = true;
	return (scene);
}
