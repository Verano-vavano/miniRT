/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:20:44 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 14:27:52 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_vec3	vec3_mult_float(t_vec3 v, float n)
{
	t_vec3	ret;

	ret.valid = v.valid;
	ret.x = v.x * n;
	ret.y = v.y * n;
	ret.z = v.z * n;
	return (ret);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	return (vec3_mult_float(v, 1 / vec3_length(v)));
}

float	vec3_length(t_vec3 v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

float	vec3_dist(t_vec3 v1, t_vec3 v2)
{
	return (sqrt(pow(v1.x - v2.x, 2)
		+ pow(v1.y - v2.y, 2)
		+ pow(v1.z - v2.z, 2)));
}

inline t_vec3	vec3_lin_comb(double alpha, t_vec3 a, double beta, t_vec3 b)
{
	return (vec3_add(vec3_mult_float(a, alpha), vec3_mult_float(b, beta)));
}

