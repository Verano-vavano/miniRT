#ifndef RENDER_H
# define RENDER_H

# include "scene.h"
# include "math.h"
# include "mlx.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_window {
	void	*mlx_ptr;
	void	*window;
	t_data	img;
	int	width;
	int	height;
	double	aspect_ratio;
	t_scene	*scene;
}	t_window;

void	render(t_scene *scene);
void	render_scene(t_window **window_ptr);

// ray_casting
t_color	cast_ray(t_window *win, t_vec2 *coord);

// mlx_plus
void	custom_mlx_pixel_put(t_data *data, int x, int y, int color);

// events
int	quit_game(t_window *window);
int	key_event(int key, t_window *window);

#endif
