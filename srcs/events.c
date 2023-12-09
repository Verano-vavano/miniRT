/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:40:01 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/09 01:25:08 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

int	quit_game(t_window *window)
{
	if (ft_strcmp(OS, "Linux") == 0)
		mlx_loop_end(window->mlx_ptr);
	mlx_destroy_window(window->mlx_ptr, window->window);
	if (ft_strcmp(OS, "Linux") == 0)
		mlx_destroy_display(window->mlx_ptr);
	free_scene(window->scene);
	free(window);
	exit(0);
}
