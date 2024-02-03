/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:48:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/03 04:04:32 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	sphere_transform(t_sphere *sp, t_transform t)
{
	if (t.type == 'r')
		return ;
	sp->pos.x += t.x;
	sp->pos.y += t.y;
	sp->pos.z += t.z;
}

void	apply_transformation(t_lform select, t_transform transform)
{
	if (select.shape == 's')
		sphere_transform((t_sphere *) select.addr, transform);
	printf("%c %d %d %d\n", select.shape, transform.x, transform.y, transform.z);
}
