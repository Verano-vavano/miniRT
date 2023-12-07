#ifndef RENDER_H
# define RENDER_H

# include "scene.h"
# include "math.h"
# include "mlx.h"

typedef struct s_window {
	void	*mlx_ptr;
	void	*window;
	int	width;
	int	height;
	double	aspect_ratio;
	t_scene	*scene;
}	t_window;

void	render(t_scene *scene);

// ray_casting
t_color	cast_ray(t_window *win, t_vec2 *coord);

// events
int	quit_game(t_window *window);

#endif
