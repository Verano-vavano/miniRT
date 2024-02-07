/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:19:14 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 17:59:42 by hdupire          ###   ########.fr       */
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
}	t_lform;

typedef struct s_hit
{
	double	t;
	bool	has_hit;
	t_vec3	hit;
	t_vec3	normal;
	t_col01	color;
	t_shade	*shade;
}				t_hit;

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

typedef struct s_lcont
{
	t_col01	lgt_contr;
	t_col01	amb_contr;
}				t_lcont;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*window;
	t_data		img;
	int			width;
	int			height;
	double		aspect_ratio;
	float		fov;
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
t_color	cast_ray(t_window *window, t_ray ray, int ray_num);
void	calculate_ray(t_ray *ray, t_window *window, t_vec2 *coord, float fov);
t_vec3	calc_ray_point(t_ray ray, double hit);
t_hit	trace(t_scene *scene, t_ray ray, t_lform *lform, bool planes);

// renderers
bool	sp_render(t_sphere *sp, t_ray r, t_hit *x, t_lform *lf);
bool	pl_render(t_plane *pl, t_ray r, t_hit *x, t_lform *lf);
bool	plane_intersect(t_plane *pl, t_ray ray, double *hit);
bool	cyl_render(t_cylinder *cyl, t_ray r, t_hit *x, t_lform *lf);
bool	check_cyl_planes(t_plane *p, t_ray ray, t_hit *hit, float radius);
bool	check_cyl_center(t_cylinder *cyl, t_ray ray, t_hit *hit);

// camera
t_vec3	cam2world(float m[4][4], t_vec3 *v);
void	lookat(t_window *window);

// lf_infos
void	get_infos(t_vec3 hit, t_lform *lf);

// light_pathing
void	ambient_lighting(struct s_ambient amb, t_col01 *ret, t_col01 lf);
void	dir_lighting(t_scene *sc, t_hit *hit, t_col01 *ret);
void	sph_lighting(t_scene *sc, t_hit *hit, t_col01 *ret);

// shading
void	reflect_color(t_window *window, t_hit *hit, t_vec3 old_dir, int r_num);

// mlx_plus
void	custom_mlx_pixel_put(t_data *data, int x, int y, int color);

// events
int		quit_game(t_window *window);
int		key_event(int key, t_window *window);
int		mousedown(int button, int x, int y, t_window *window);
int		unminimize(t_window *window);

// transformations
void	apply_transformation(t_lform select, t_transform transform);
void	size_modif(t_window *window, char key, t_lform lf);

// render_utilities
void	copy_color(t_color *col, uint8_t r, uint8_t g, uint8_t b);
t_col01	copy_col_to_01(t_color col);
void	copy_2vec3(t_vec3 *v1, t_vec3 v2);
void	keyboard_conf(t_window *window);
bool	quadratic(double a, double b, double c, double *ret);
float	to_rad(int n);
void	init_lgt_contr(t_lcont *contr);

#endif
