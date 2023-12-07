#ifndef VECTORS_H
# define VECTORS_H

#include <stdbool.h>
#include <math.h>

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
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	bool		valid;
}		t_color;

double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_mult_float(t_vec3 v, float n);
t_vec3	vec3_normalize(t_vec3 v);
float	vec3_length(t_vec3 v);

#endif
