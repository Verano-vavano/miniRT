/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:48:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/12 16:06:01 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	copy_color(t_color *col, uint8_t r, uint8_t g, uint8_t b)
{
	col->r = r;
	col->g = g;
	col->b = b;
	return ;
}

void	copy_2vec3(t_vec3 *v1, t_vec3 v2)
{
	v1->x = v2.x;
	v1->y = v2.y;
	v1->z = v2.z;
	return ;
}
