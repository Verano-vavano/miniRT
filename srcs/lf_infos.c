/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:17:07 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 08:53:02 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* LF shapes :
 * 's' = sphere
 * 'p' = plane
 */
void	get_infos(t_vec3 hit, t_lform *lf)
{
	t_color		temp;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cl;

	lf->normal.x = 0;
	lf->normal.y = 0;
	lf->normal.z = 0;
	lf->shade = NULL;
	if (lf->shape == 's')
	{
		sp = (t_sphere *) lf->addr;
		copy_color(&temp, sp->color.r, sp->color.g, sp->color.b);
		copy_2vec3(&(lf->normal), vec3_normalize(vec3_sub(hit, sp->pos)));
		lf->shade = &(sp->shading);
	}
	else if (lf->shape == 'p')
	{
		pl = (t_plane *) lf->addr;
		copy_color(&temp, pl->color.r, pl->color.g, pl->color.b);
		copy_2vec3(&(lf->normal), pl->normal);
		lf->shade = &(pl->shading);
	}
	else if (lf->shape == 'c')
	{
		cl = (t_cylinder *) lf->addr;
		copy_color(&temp, cl->color.r, cl->color.g, cl->color.b);
		copy_2vec3(&(lf->normal), cl->dir);
		lf->shade = &(cl->shading);
	}
	lf->color.r = temp.r / 255.f;
	lf->color.g = temp.g / 255.f;
	lf->color.b = temp.b / 255.f;
}
