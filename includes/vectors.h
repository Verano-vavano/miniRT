/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:13:29 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 08:45:45 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <stdbool.h>
# include <math.h>
# include <stdint.h>

typedef struct s_vec2
{
	double	x;
	double	y;
}		t_vec2;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
	bool	valid;
}		t_vec3;

typedef struct s_ray
{
	t_vec3	org;
	t_vec3	dir;
}		t_ray;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	bool	valid;
}		t_color;

typedef struct s_col01
{
	float	r;
	float	g;
	float	b;
}		t_col01;

double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_mult_float(t_vec3 v, float n);
t_vec3	vec3_normalize(t_vec3 v);
float	vec3_length(t_vec3 v);
float	vec3_dist(t_vec3 v1, t_vec3 v2);

#endif
