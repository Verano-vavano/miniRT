/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:40:01 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/08 23:24:45 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	mlx_loop_end(void *ptr) { (void) ptr; }
void	mlx_destroy_display(void *ptr) { (void) ptr; }

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
