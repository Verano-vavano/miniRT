/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrices.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:49:46 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 19:51:11 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	get_mat_x(float mat_x[3][3], float angle)
{
	mat_x[0][0] = 1;
	mat_x[0][1] = 0;
	mat_x[0][2] = 0;
	mat_x[1][0] = 0;
	mat_x[1][1] = cos(angle);
	mat_x[1][2] = sin(angle);
	mat_x[2][0] = 0;
	mat_x[2][1] = -sin(angle);
	mat_x[2][2] = cos(angle);
}

void	get_mat_y(float mat_y[3][3], float angle)
{
	mat_y[0][0] = cos(angle);
	mat_y[0][1] = 0;
	mat_y[0][2] = -sin(angle);
	mat_y[1][0] = 0;
	mat_y[1][1] = 1;
	mat_y[1][2] = 0;
	mat_y[2][0] = sin(angle);
	mat_y[2][1] = 0;
	mat_y[2][2] = cos(angle);
}

void	get_mat_z(float mat_z[3][3], float angle)
{
	mat_z[0][0] = cos(angle);
	mat_z[0][1] = sin(angle);
	mat_z[0][2] = 0;
	mat_z[1][0] = -sin(angle);
	mat_z[1][1] = cos(angle);
	mat_z[1][2] = 0;
	mat_z[2][0] = 0;
	mat_z[2][1] = 0;
	mat_z[2][2] = 1;
}
