/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:53:15 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 14:26:07 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vectors.h"

enum e_scene_arg
{
	AMBIENT,
	CAMERA,
	DIR_LIGHT,
	SPH_LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
};

struct	s_camera
{
	t_vec3	vp;
	t_vec3	dir;
	short	fov;
};

struct	s_ambient
{
	float	lgt_ratio;
	t_color	color;
};

typedef struct s_light
{
	t_vec3			vec;
	t_vec3			inv_dir;
	float			lgt_ratio;
	t_color			color;
	bool			spherical;
	struct s_light	*next_light;
}				t_light;

typedef struct s_lighting
{
	t_light		*light;
	t_light		*last_light;
	t_light		*s_light;
	t_light		*last_s_light;
	t_light		*movable;
}				t_lighting;

typedef struct s_shade
{
	bool	reflect;
}				t_shade;

typedef struct s_sphere
{
	t_vec3			pos;
	float			diameter;
	t_color			color;
	t_shade			shading;
	struct s_sphere	*next_sphere;
}				t_sphere;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_color			color;
	t_shade			shading;
	struct s_plane	*next_plane;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3				center;
	t_vec3				p_bot;
	t_vec3				p_top;
	t_vec3				dir;
	float				diameter;
	float				radius;
	float				height;
	t_color				color;
	t_shade				shading;
	struct s_cylinder	*next;
}		t_cylinder;

typedef struct s_scene
{
	bool				is_valid;
	bool				has_camera;
	bool				has_ambient;
	struct s_camera		camera;
	struct s_ambient	ambient;
	t_lighting			lighting;
	t_sphere			*spheres;
	t_sphere			*last_sphere;
	t_plane				*planes;
	t_plane				*last_plane;
	t_cylinder			*cyl;
	t_cylinder			*last_cyl;
}				t_scene;

#endif
