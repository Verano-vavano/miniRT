/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:17:07 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/12 16:05:40 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* LF shapes :
 * 's' = sphere
 * 'p' = plane
 */
void	get_infos(t_vec3 hit, t_lform *lf, t_vec3 *normal, t_col01 *col)
{
	t_color	temp;

	normal->x = 0;
	normal->y = 0;
	normal->z = 0;
	if (lf->shape == 's')
	{
		struct s_sphere *sp = (struct s_sphere *) lf->addr;
		copy_color(&temp, sp->color.r, sp->color.g, sp->color.b);
		copy_2vec3(normal, vec3_normalize(vec3_sub(hit, sp->pos)));
	}
	else if (lf->shape == 'p')
	{
		struct s_plane *pl = (struct s_plane *) lf->addr;
		copy_color(&temp, pl->color.r, pl->color.g, pl->color.b);
		copy_2vec3(normal, pl->normal);
	}
	col->r = temp.r / 255.f;
	col->g = temp.g / 255.f;
	col->b = temp.b / 255.f;
}
