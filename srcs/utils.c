/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:10:52 by hdupire           #+#    #+#             */
/*   Updated: 2024/01/31 23:14:22 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	quadratic(double a, double b, double c, double *ret)
{
	double	discr, x_hit1, x_hit2;

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
