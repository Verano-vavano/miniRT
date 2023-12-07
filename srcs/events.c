/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:40:01 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/06 13:59:28 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	quit_game(t_window *window)
{
	mlx_loop_end(window->mlx_ptr);
	mlx_destroy_window(window->mlx_ptr, window->window);
	mlx_destroy_display(window->mlx_ptr);
	free_scene(window->scene);
	free(window);
	exit(0);
}
