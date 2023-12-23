/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 05:20:29 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/22 18:43:44 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

static bool	understand_scene_line(t_scene *scene, char *line)
{
	char	*item;
	bool	ret;

	item = get_line_arg(line, NULL);
	if (!item)
		return (true);
	ret = true;
	if (ft_strcmp(item, "A") == 0)
		ret = adder(scene, line, &(scene->has_ambient), 'A');
	else if (ft_strcmp(item, "C") == 0)
		ret = adder(scene, line, &(scene->has_camera), 'C');
	else if (ft_strcmp(item, "L") == 0)
		ret = adder(scene, line, NULL, 'L');
	else if (ft_strcmp(item, "sp") == 0)
		ret = adder(scene, line, NULL, 's');
	else if (ft_strcmp(item, "pl") == 0)
		ret = adder(scene, line, NULL, 'p');
	free(item);
	return (ret);
}

static void	read_scene_file(t_scene *scene, int file_fd)
{
	char	*buffer;
	bool	ret;

	buffer = get_next_line(file_fd);
	ret = true;
	while (buffer)
	{
		ret = understand_scene_line(scene, buffer);
		free(buffer);
		if (!ret)
		{
			scene->is_valid = false;
			break ;
		}
		buffer = get_next_line(file_fd);
	}
	close(file_fd);
}

t_scene	*get_scene(char *file)
{
	t_scene	*scene;
	int	file_fd;

	scene = ft_calloc(1, sizeof (t_scene));
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
