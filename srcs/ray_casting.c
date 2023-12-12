/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/12 14:54:25 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

#define _USE_MATH_DEFINES

/*
static void	apply_ambient(struct s_ambient a, t_color *c)
{
	c->r *= a.lgt_ratio * (a.color.r / 255.0f);
	c->g *= a.lgt_ratio * (a.color.g / 255.0f);
	c->b *= a.lgt_ratio * (a.color.b / 255.0f);
}*/

static void	apply_light(struct s_light l, t_vec3 hit, t_color *c)
{
	double	d;

	d = l.lgt_ratio * fmax(vec3_dot(vec3_mult_float(vec3_normalize(l.pos), -1.0f), hit), 0.0f);
	c->r = (int) (c->r * d);
	c->g = (int) (c->g * d);
	c->b = (int) (c->b * d);
}

/* RAY_CASTING
 * Must return the color of the pixel pointed to by coord
 * Colors are as such 0x00RRGGBB
 */
t_color	cast_ray(t_window *win, t_vec2 *coord)
{
	t_vec2	normalized_coord;
	t_vec3	direction;
	t_vec3	origin;
	t_color	ret;
	float	fov;
	double	a, b, c, discr, x_hit, x_hit1, x_hit2;

	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	fov = win->scene->camera.fov * M_PI / 180;
	normalized_coord.x = (2.0f * (coord->x + 0.5f) / win->width - 1.0f) * win->aspect_ratio * tan(fov / 2);
	normalized_coord.y = (1.0f - 2.0f * (coord->y + 0.5f) / win->height) * tan(fov / 2);
	direction.x = normalized_coord.x;
	direction.y = normalized_coord.y;
	direction.z = win->scene->camera.dir.z;
	direction = vec3_normalize(direction);
	origin = win->scene->camera.vp;
	a = vec3_dot(direction, direction);
	b = 2.0f * vec3_dot(origin, direction);
	c = vec3_dot(origin, origin) - pow(win->scene->last_sphere->diameter / 2, 2);
	discr = pow(b, 2) - (4 * a * c);
	if (discr < 0)
	{
		//apply_ambient(win->scene->ambient, &ret);
		return (ret);
	}
	x_hit1 = (-b + sqrt(discr)) / (2 * a);
	x_hit2 = (-b - sqrt(discr)) / (2 * a);
	if (x_hit1 >= 0 && (x_hit2 < 0 || x_hit1 < x_hit2))
		x_hit = x_hit1;
	else if (x_hit2 >= 0 && (x_hit1 < 0 || x_hit2 < x_hit1))
		x_hit = x_hit2;
	else
		return (ret);
	t_vec3	hit = vec3_normalize(vec3_add(origin, vec3_mult_float(direction, x_hit)));

	ret.r = 255;
	ret.g = 0;
	ret.b = 0;
	//apply_ambient(win->scene->ambient, &ret);
	apply_light(win->scene->light, hit, &ret);
	return (ret);
}
