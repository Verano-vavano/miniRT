#ifndef VECTORS_H
# define VECTORS_H

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

#endif
