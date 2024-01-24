/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_plus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 21:06:04 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/23 21:06:41 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	custom_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		i;

	i = data->bits_per_pixel - 8;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	while (i >= 0)
	{
		if (data->endian != 0)
			*dst++ = (color >> i) & 0xFF;
		else
			*dst++ = (color >> (data->bits_per_pixel - 8 - i)) & 0xFF;
		i -= 8;
	}
}
