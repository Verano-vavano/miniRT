/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/07 23:55:15 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

static t_color	apply_ambient(struct s_ambient a, t_color c)
{
	t_color	ret;

	ret.r = c.r * a.lgt_ratio * (a.color.r / 255.0f);
	ret.g = c.g * a.lgt_ratio * (a.color.g / 255.0f);
	ret.b = c.b * a.lgt_ratio * (a.color.b / 255.0f);
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

	ret.r = 255;
	ret.g = 255;
	ret.b = 255;
	direction.x = (2.0f * coord->x / win->width - 1.0f) * win->aspect_ratio;
	direction.y = 1.0f - 2.0f * coord->y / win->height;
	direction.z = 1.0f;
	origin = win->scene->camera.vp;
	a = vec3_dot(direction, direction);
	b = 2.0f * vec3_dot(origin, direction);
	c = vec3_dot(origin, origin) - pow(win->scene->last_sphere->diameter / 2, 2);
	discr = pow(b, 2) - (4 * a * c);
	if (discr < 0)
		return (apply_ambient(win->scene->ambient, ret));
	x_hit = fmin((-b + sqrt(discr)) / (2 * a), (-b - sqrt(discr)) / (2 * a));
	t_vec3	hit = vec3_normalize(vec3_add(origin, vec3_mult_float(direction, x_hit)));

	ret.r = (uint8_t) ((hit.x + 1.0f) * 0.5f * 255.0f);
	ret.g = (uint8_t) ((hit.y + 1.0f) * 0.5f * 255.0f);
	ret.b = (uint8_t) ((hit.z + 1.0f) * 0.5f * 255.0f);
	return (apply_ambient(win->scene->ambient, ret));
}
