/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/07 16:01:48 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

/* RAY_CASTING
 * Must return the color of the pixel pointed to by coord
 * Colors are as such 0x00RRGGBB
 */
int	cast_ray(t_window *win, t_vec2 *coord)
{
	t_vec3	direction;
	t_vec3	origin;
	double	a, b, c, discr, x_hit;

	direction.x = (2.0f * coord->x / win->width - 1.0f) * win->aspect_ratio;
	direction.y = 1.0f - 2.0f * coord->y / win->height;
	direction.z = 1.0f;
	origin = win->scene->camera.vp;
	a = vec3_dot(direction, direction);
	b = 2.0f * vec3_dot(origin, direction);
	c = vec3_dot(origin, origin) - pow(win->scene->last_sphere->diameter / 2, 2);
	discr = pow(b, 2) - (4 * a * c);
	if (discr > 0)
	{
		x_hit = fmin((-b + sqrt(discr)) / (2 * a), (-b - sqrt(discr)) / (2 * a));
		t_vec3	hit = vec3_add(origin, vec3_mult_float(direction, x_hit));

		uint8_t	r, g, b;
		r = (uint8_t) (hit.x * 255.0f);
		g = (uint8_t) (hit.y * 255.0f);
		b = (uint8_t) (hit.z * 255.0f);
		return (b * 1000000 + g * 1000 + r);
	}
	else
		return (0x00ffffff);
}
