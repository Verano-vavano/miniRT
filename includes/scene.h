#ifndef SCENE_H
# define SCENE_H

# include "main.h"
# include "render.h"

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

typedef struct	s_scene {
	bool			is_valid;
	bool			has_camera;
	bool			has_ambiant;
	struct s_camera		camera;
	struct s_ambient	ambient;
}		t_scene;

t_scene	*get_scene(char *file);

char	*get_line_arg(char *line, int *adv);

bool	add_ambiant(t_scene *scene, char *line);

#endif
