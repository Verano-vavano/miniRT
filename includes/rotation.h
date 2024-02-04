/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 21:26:14 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 19:58:13 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_H
# define ROTATION_H

# include "vectors.h"

void	apply_rotation(t_vec3 *v, float x, float y, float z);
void	get_mat_x(float mat_x[3][3], float angle);
void	get_mat_y(float mat_y[3][3], float angle);
void	get_mat_z(float mat_z[3][3], float angle);

#endif
