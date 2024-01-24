/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:35:34 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/23 20:36:30 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	free_spheres(t_sphere *spheres)
{
	t_sphere	*next;

	while (spheres)
	{
		next = spheres->next_sphere;
		free(spheres);
		spheres = next;
	}
	return ;
}

static void	free_planes(t_plane *planes)
{
	t_plane	*next;

	while (planes)
	{
		next = planes->next_plane;
		free(planes);
		planes = next;
	}
	return ;
}

static void	free_lights(t_light *light)
{
	t_light	*next;

	while (light)
	{
		next = light->next_light;
		free(light);
		light = next;
	}
	return ;
}

void	free_scene(t_scene *scene)
{
	free_spheres(scene->spheres);
	free_planes(scene->planes);
	free_lights(scene->lighting.light);
	free_lights(scene->lighting.s_light);
	free(scene);
	return ;
}
