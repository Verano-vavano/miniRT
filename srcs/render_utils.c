/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:48:12 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 19:49:08 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	copy_2vec3(t_vec3 *v1, t_vec3 v2)
{
	v1->x = v2.x;
	v1->y = v2.y;
	v1->z = v2.z;
	return ;
}

inline t_vec3	calc_ray_point(t_ray ray, double hit)
{
	return (vec3_add(ray.org, vec3_mult_float(ray.dir, hit)));
}

bool	quadratic(double a, double b, double c, double *ret)
{
	double	discr;
	double	x_hit1;
	double	x_hit2;

	discr = pow(b, 2) - (4 * a * c);
	if (discr < 0)
		return (false);
	discr = sqrt(discr);
	x_hit1 = - (b + discr) / (2 * a);
	x_hit2 = - (b - discr) / (2 * a);
	if (x_hit1 >= 0 && (x_hit2 < 0 || x_hit1 < x_hit2))
		*ret = x_hit1;
	else if (x_hit2 >= 0 && (x_hit1 < 0 || x_hit2 < x_hit1))
		*ret = x_hit2;
	else
		return (false);
	return (true);
}

inline float	to_rad(int n)
{
	return ((float) n / 180 * M_PI);
}

void	init_lgt_contr(t_lcont *contr)
{
	contr->lgt_contr.r = 0;
	contr->lgt_contr.g = 0;
	contr->lgt_contr.b = 0;
	contr->amb_contr.r = 0;
	contr->amb_contr.g = 0;
	contr->amb_contr.b = 0;
}
