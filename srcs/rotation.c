/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:27:23 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 18:38:59 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include <stdio.h>

static void	mult_3x3(float ret[3][3], float a[3][3], float b[3][3])
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			ret[i][j] = 0;
			k = -1;
			while (++k < 3)
				ret[i][j] += a[i][k] * b[k][j];
		}
	}
}

static void	rotmat(float rot[3][3], float x[3][3], float y[3][3], float z[3][3])
{
	float	xy[3][3];

	mult_3x3(xy, x, y);
	mult_3x3(rot, xy, z);
}

void	apply_rotation(t_vec3 *v, float x, float y, float z)
{
	float	mat_x[3][3];
	float	mat_y[3][3];
	float	mat_z[3][3];
	float	rot[3][3];
	t_vec3	new_v;

	get_mat_x(mat_x, x);
	get_mat_y(mat_y, y);
	get_mat_z(mat_z, z);
	rotmat(rot, mat_x, mat_y, mat_z);
	new_v.x = v->x * rot[0][0] + v->y * rot[0][1] + v->z * rot[0][2];
	new_v.y = v->x * rot[1][0] + v->y * rot[1][1] + v->z * rot[1][2];
	new_v.z = v->x * rot[2][0] + v->y * rot[2][1] + v->z * rot[2][2];
	if (new_v.z > 0)
		new_v = vec3_mult_float(new_v, -1.f);
	new_v = vec3_normalize(new_v);
	v->x = new_v.x;
	v->y = new_v.y;
	v->z = new_v.z;
}
