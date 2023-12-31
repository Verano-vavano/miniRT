/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:35:34 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/22 18:50:43 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	free_spheres(struct s_sphere *spheres)
{
	struct s_sphere	*next;

	while (spheres)
	{
		next = spheres->next_sphere;
		free(spheres);
		spheres = next;
	}
	return ;
}

static void	free_planes(struct s_plane *planes)
{
	struct s_plane	*next;

	while (planes)
	{
		next = planes->next_plane;
		free(planes);
		planes = next;
	}
	return ;
}

void	free_scene(t_scene *scene)
{
	free_spheres(scene->spheres);
	free_planes(scene->planes);
	free(scene);
	return ;
}
