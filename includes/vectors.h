#ifndef VECTORS_H
# define VECTORS_H

#include <stdbool.h>
#include <math.h>
#include <stdint.h>

typedef struct	s_vec2 {
	double	x;
	double	y;
}		t_vec2;

typedef struct	s_vec3 {
	double	x;
	double	y;
	double	z;
	bool	valid;
}		t_vec3;

typedef struct	s_color {
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	bool		valid;
}		t_color;

double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_mult_float(t_vec3 v, float n);
t_vec3	vec3_normalize(t_vec3 v);
float	vec3_length(t_vec3 v);

#endif
