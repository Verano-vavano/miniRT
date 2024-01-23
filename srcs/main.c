/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 03:56:46 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/23 11:30:58 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "scene.h"
#include "errors.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (parsing_err(argc, argv))
		return (1);
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
	render(scene);
	free_scene(scene);
	return (0);
}
