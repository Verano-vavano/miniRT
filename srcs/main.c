/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 03:56:46 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/05 21:33:57 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "scene.h"

static bool	is_rt_file(char *f)
{
	int	i;

	i = 0;
	while (f[i])
		i++;
	return (i >= 3 && f[i - 1] == 't' && f[i - 2] == 'r'
		&& f[i - 3] == '.');
}

static bool	is_argv_valid(int argc, char **argv)
{
	return (argc >= 2 && access(argv[1], R_OK) == 0
		&& is_rt_file(argv[1]));
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (!is_argv_valid(argc, argv))
	{
		printf("Error\n");
		printf("Please enter a valid argument\n");
		return (1);
	}

	scene = get_scene(argv[1]);
	if (!scene)
	{
		printf("Error\nMalloc error\n");
		return (1);
	}
	if (!scene->is_valid)
	{
		printf("Error\n");
		printf("The scene entered is invalid (see log above)\n");
		free_scene(scene);
		return (1);
	}
	render_scene(scene);
	free_scene(scene);
	return (0);
}
