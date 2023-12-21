/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:26:12 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/21 18:44:45 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*static void	apply_light(struct s_light l, t_vec3 hit, t_color *c)
{
	double	d;

	d = l.lgt_ratio * fmax(vec3_dot(vec3_mult_float(vec3_normalize(l.pos), -1.0f), hit), 0.0f);
	c->r = (int) (c->r * d);
	c->g = (int) (c->g * d);
	c->b = (int) (c->b * d);
}*/

t_color	light_pathing(t_vec3 origin, t_vec3 direction, struct s_light l, double x_hit, t_color base_color)
{
	(void) origin;
	(void) direction;
	(void) l;
	(void) x_hit;
	//t_vec3	hit = vec3_normalize(vec3_add(origin, vec3_mult_float(direction, x_hit)));
	//apply_ambient(win->scene->ambient, &ret);
	//apply_light(l, hit, &base_color);
	return (base_color);
}
