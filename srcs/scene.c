/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 05:20:29 by hdupire           #+#    #+#             */
/*   Updated: 2023/11/30 00:18:08 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

// POUR DEMAIN :
// SCENE_READ_UTILITIES
// Envoie l'argument pointé
// A 255,255,255 12
// Renvoie A, et ignore leading spaces
// Renvoie NULL si \n
//
// Remplir t_scene
// Camera, ambiant, light, formes
//
// Trouver solutions pour différentes formes (pas urgent, d'abord sp)

// Returns true if no error has been encountered and the line was understood
// Else returns false
static bool	understand_scene_line(t_scene *scene, char *line)
{
	char	*item;

	printf("LINE = %s", line);
	advancement = 0;
	item = get_line_arg(line, NULL);
	if (ft_strcmp(item, "A") == 0)
		return (add_ambiant(scene));
	/*
	while (understander)
	{
		printf("-%s\n", understander);
		free(understander);
		line += advancement;
		understander = get_line_arg(line, &advancement);
	}*/
	return (false);
}

static void	read_scene_file(t_scene *scene, int file_fd)
{
	char	*buffer;

	buffer = get_next_line(file_fd);
	while (buffer)
	{
		understand_scene_line(scene, buffer);
		free(buffer);
		if (scene->is_valid == false)
			break ;
		buffer = get_next_line(file_fd);
	}
	close(file_fd);
}

t_scene	*get_scene(char *file)
{
	t_scene	*scene;
	int	file_fd;

	scene = malloc(sizeof (t_scene));
	if (!scene)
		return (NULL);
	scene->is_valid = true;
	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
	{
		write(2, "Cannot open file\n", 17);
		scene->is_valid = false;
	}
	else
		read_scene_file(scene, file_fd);
	return (scene);
}
