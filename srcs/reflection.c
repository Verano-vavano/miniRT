/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 10:57:01 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/05 01:18:39 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	reflect_color(t_window *window, t_hit *hit, t_vec3 old_dir, int r_num)
{
	t_ray	new_ray;
	t_color	ret;

	new_ray.org = vec3_add(hit->hit, vec3_mult_float(hit->normal, SHADOW_BIAS));
	new_ray.dir = vec3_sub(old_dir, vec3_mult_float(hit->normal,
				2 * vec3_dot(hit->normal, old_dir)));
	new_ray.dir = vec3_normalize(new_ray.dir);
	ret = cast_ray(window, new_ray, r_num + 1);
	hit->color.r = ret.r / 255.f;
	hit->color.g = ret.g / 255.f;
	hit->color.b = ret.b / 255.f;
}
