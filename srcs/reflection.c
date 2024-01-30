/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:57:01 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/29 02:58:09 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	reflect_color(t_window *window, t_vec3 hit, t_vec3 old_dir, t_lform *lf, int r_num)
{
	t_ray	new_ray;

	new_ray.org = vec3_add(hit, vec3_mult_float(lf->normal, SHADOW_BIAS));
	new_ray.dir = vec3_sub(old_dir, vec3_mult_float(lf->normal, 2 * vec3_dot(lf->normal, old_dir)));
	new_ray.dir = vec3_normalize(new_ray.dir);
	return (cast_ray(window, new_ray, r_num + 1));
}
