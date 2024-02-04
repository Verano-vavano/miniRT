/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:47:40 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 14:51:41 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_vec3	cam2world(float m[4][4], t_vec3 *v)
{
	t_vec3	dst;

	dst.x = v->x * m[0][0] + v->y * m[1][0] + v->z * m[2][0];
	dst.y = v->x * m[0][1] + v->y * m[1][1] + v->z * m[2][1];
	dst.z = v->x * m[0][2] + v->y * m[1][2] + v->z * m[2][2];
	return (dst);
}

void	lookat(t_window *window)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	tmp;

	tmp.x = 0;
	tmp.y = 1;
	tmp.z = 0;
	forward = window->scene->camera.dir;
	if (forward.x == 0 && forward.y == 0 && forward.z == 0)
		forward.z = 1;
	forward = vec3_normalize(forward);
	right = vec3_cross(tmp, forward);
	up = vec3_cross(forward, right);
	window->cam[0][0] = right.x;
	window->cam[0][1] = right.y;
	window->cam[0][2] = right.z;
	window->cam[1][0] = up.x;
	window->cam[1][1] = up.y;
	window->cam[1][2] = up.z;
	window->cam[2][0] = forward.x;
	window->cam[2][1] = forward.y;
	window->cam[2][2] = forward.z;
}
