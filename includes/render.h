/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:19:14 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 08:44:06 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "objects.h"
# include "scene.h"
# include "math.h"
# include "mlx.h"

# include "render_options.h"

typedef struct s_last_form
{
	void	*addr;
	char	shape;
	t_col01	color;
	t_vec3	normal;
	t_shade	*shade;
}	t_lform;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_transform
{
	char	type;
	int		x;
	int		y;
	int		z;
	int		temp;
}				t_transform;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*window;
	t_data		img;
	int			width;
	int			height;
	double		aspect_ratio;
	float		cam[4][4];
	char		keyboard;
	bool		rmb_pressed;
	bool		height_mod;
	t_lform		last_selected;
	t_transform	transform;
	t_scene		*scene;
}	t_window;

void	render(t_scene *scene);
void	render_scene(t_window **window_ptr);
void	lookat(t_window *window);
t_color	cast_ray(t_window *window, t_ray ray, int ray_num);
void	calculate_ray(t_ray *ray, t_window *window, t_vec2 *coord, float fov);
t_vec3	calc_ray_point(t_ray ray, double hit);
double	trace(t_scene *scene, t_ray ray, t_lform *lform, bool planes);

// renderers
bool	sp_render(t_sphere *sp, t_ray r, double *x, t_lform *lf);
bool	pl_render(t_plane *pl, t_ray r, double *x, t_lform *lf);
bool	plane_intersect(t_plane *pl, t_ray ray, double *hit);
bool	cyl_render(t_cylinder *cyl, t_ray r, double *x, t_lform *lf);

// lf_infos
void	get_infos(t_vec3 hit, t_lform *lf);

// light_pathing
void	ambient_lighting(struct s_ambient amb, t_col01 *ret, t_col01 lf);
void	dir_lighting(t_scene *sc, t_vec3 hit, t_col01 *ret, t_lform *lf);
void	sph_lighting(t_scene *sc, t_vec3 hit, t_col01 *ret, t_lform *lf);

// shading
t_color	reflect_color(t_window *window, t_vec3 hit, t_vec3 old_dir, t_lform *lf, int r_num);

// mlx_plus
void	custom_mlx_pixel_put(t_data *data, int x, int y, int color);

// events
int		quit_game(t_window *window);
int		key_event(int key, t_window *window);
int		mousedown(int button, int x, int y, t_window *window);

// transformations
void	apply_transformation(t_lform select, t_transform transform);

// render_utilities
void	copy_color(t_color *col, uint8_t r, uint8_t g, uint8_t b);
void	copy_2vec3(t_vec3 *v1, t_vec3 v2);
void	keyboard_conf(t_window *window);

// utils
bool	quadratic(double a, double b, double c, double *ret);

#endif
