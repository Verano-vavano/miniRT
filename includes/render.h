#ifndef RENDER_H
# define RENDER_H

# include "scene.h"
# include "math.h"
# include "mlx.h"

# include "render_options.h"

typedef struct s_last_form {
	void	*addr;
	char	shape;
}	t_lform;

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

// renderers
bool	spheres_render_all(struct s_sphere *sp, t_vec3 org, t_vec3 dir, double *x, t_lform *lform);
bool	planes_render_all(struct s_plane *pl, t_vec3 org, t_vec3 dir, double *x, t_lform *lform);

// lf_infos
void	get_infos(t_vec3 hit, t_lform *lf, t_vec3 *normal, t_col01 *col);

// light_pathing
void	light_pathing(t_scene *scene, t_vec3 normal, t_col01 *ret);

// mlx_plus
void	custom_mlx_pixel_put(t_data *data, int x, int y, int color);

// events
int	quit_game(t_window *window);
int	key_event(int key, t_window *window);

// render_utilities
void	copy_color(t_color *col, uint8_t r, uint8_t g, uint8_t b);
void	copy_2vec3(t_vec3 *v1, t_vec3 v2);

#endif
