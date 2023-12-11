/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/09 17:53:04 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

/* AMBIENT
 * R = (COLOR.r / 255) * LIGHT_RATIO * (LIGHT_COLOR.r / 255)
 */
static t_fcolor	apply_ambient(struct s_ambient a, t_color c)
{
	t_fcolor	ret;

	ret.r = c.r * a.lgt_ratio * a.color.r / 65025;
	ret.g = c.g * a.lgt_ratio * a.color.g / 65025;
	ret.b = c.b * a.lgt_ratio * a.color.b / 65025;
	return (ret);
}

/* DIRECTIONAL LIGHT
 * Dir = Dot product of Normal of Light and Normal of hit point
 * Then
 * R = (LIGHT_COLOR.r / 255) * Dir
 */
static t_fcolor	apply_light(struct s_light l, t_vec3 hit)
{
	t_fcolor	ret;
	double		d;

	d = fmax(vec3_dot(vec3_mult_float(vec3_normalize(l.pos), -1.0f), hit), 0.0f);
	ret.r = l.color.r * d / 255.0f;
	ret.g = l.color.g * d / 255.0f;
	ret.b = l.color.b * d / 255.0f;
	return (ret);
}

/* RAY_CASTING
 * Must return the color of the pixel pointed to by coord
 * Colors are as such 0x00RRGGBB
 */
t_color	cast_ray(t_window *win, t_vec2 *coord)
{
	t_vec3	direction;
	t_vec3	origin;
	t_color	ret;
	double	a, b, c, discr, x_hit;

	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	direction.x = (2.0f * coord->x / win->width - 1.0f) * win->aspect_ratio;
	direction.y = 1.0f - 2.0f * coord->y / win->height;
	direction.z = 1.0f;
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
	x_hit = fmin((-b + sqrt(discr)) / (2 * a), (-b - sqrt(discr)) / (2 * a));
	t_vec3	hit = vec3_normalize(vec3_add(origin, vec3_mult_float(direction, x_hit)));

	t_fcolor	directional_contr, ambient_contr;
	directional_contr = apply_light(win->scene->light, hit);
	ambient_contr = apply_ambient(win->scene->ambient, win->scene->last_sphere->color);
	ret.r = fmin(255 * (directional_contr.r + ambient_contr.r), 255);
	ret.g = fmin(255 * (directional_contr.g + ambient_contr.g), 255);
	ret.b = fmin(255 * (directional_contr.b + ambient_contr.b), 255);
	return (ret);
}
