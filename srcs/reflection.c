/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:57:01 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 18:04:17 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	reflect_color(t_window *window, t_hit hit, t_vec3 old_dir, int r_num)
{
	t_ray	new_ray;

	new_ray.org = vec3_add(hit.hit, vec3_mult_float(hit.normal, SHADOW_BIAS));
	new_ray.dir = vec3_sub(old_dir, vec3_mult_float(hit.normal,
				2 * vec3_dot(hit.normal, old_dir)));
	new_ray.dir = vec3_normalize(new_ray.dir);
	return (cast_ray(window, new_ray, r_num + 1));
}
