#ifndef SCENE_H
# define SCENE_H

# include "main.h"
# include "vectors.h"

# include <fcntl.h>

struct	s_camera {
	t_vec3	vp;
	t_vec3	dir;
	short	fov;
};

struct	s_ambient {
	float	lgt_ratio;
	t_color	color;
};

struct	s_light {
	t_vec3	pos;
	float	lgt_ratio;
	t_color	color;
};

struct	s_sphere {
	t_vec3		pos;
	float		diameter;
	t_color		color;
	struct s_sphere	*next_sphere;
};

struct	s_plane {
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
	struct s_plane	*next_plane;
};

typedef struct	s_scene {
	bool			is_valid;
	bool			has_camera;
	bool			has_ambient;
	struct s_camera		camera;
	struct s_ambient	ambient;
	struct s_light		light;
	struct s_sphere		*spheres;
	struct s_sphere		*last_sphere;
	struct s_plane		*planes;
	struct s_plane		*last_plane;
}		t_scene;

# include "render.h"

// SCENE
t_scene	*get_scene(char *file);

// SCENES UTILS
char	*get_line_arg(char *line, int *adv);

void	free_scene(t_scene *scene);

// PARSER
bool	adder(t_scene *scene, char *line, bool *verif, char name);

// PARSER FORMS
bool	set_new_arg_sphere(t_scene *scene, char *arg, short arg_num);
bool	set_new_arg_plane(t_scene *scene, char *arg, short arg_num);

// CHECKER
bool	check_ambient(t_scene *scene);
bool	check_camera(t_scene *scene);
bool	check_light(t_scene *scene);
bool	check_last_sphere(t_scene *scene);
bool	check_last_plane(t_scene *scene);

// ATOF
float	little_atof(char *arg);

// COLORS
t_color	get_color(char *arg);

// VEC3
t_vec3	get_coord_vec3(char *arg, bool smallest);

#endif
