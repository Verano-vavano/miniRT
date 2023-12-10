/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/10 19:10:02 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

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

	d = fmax(vec3_dot(vec3_mult_float(vec3_normalize(l.pos), -1.0f), hit), 0.0f);
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

	ret.r = 255;
	ret.g = 0;
	ret.b = 0;
	//apply_ambient(win->scene->ambient, &ret);
	apply_light(win->scene->light, hit, &ret);
	return (ret);
}
