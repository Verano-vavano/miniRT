/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:17:07 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/10 18:45:48 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* LF shapes :
 * 's' = sphere
 * 'p' = plane
 */
t_vec3	get_normal(t_vec3 hit, t_lform *lf)
{
	t_vec3	ret;

	ret.x = 0;
	ret.y = 0;
	ret.z = 0;
	if (lf->shape == 's')
	{
		struct s_sphere *sp = (struct s_sphere *) lf->addr;
		return (vec3_normalize(vec3_sub(hit, sp->pos)));
	}
	else if (lf->shape == 'p')
	{
		struct s_plane *pl = (struct s_plane *) lf->addr;
		return (pl->normal);
	}
	return (ret);
}
