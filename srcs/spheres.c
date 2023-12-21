/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/21 18:09:19 by hdupire          ###   ########.fr       */
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
}

static void	apply_light(struct s_light l, t_vec3 hit, t_color *c)
{
	double	d;

	d = l.lgt_ratio * fmax(vec3_dot(vec3_mult_float(vec3_normalize(l.pos), -1.0f), hit), 0.0f);
	c->r = (int) (c->r * d);
	c->g = (int) (c->g * d);
	c->b = (int) (c->b * d);
}*/

/* RAY_CASTING
 * Must return the color of the pixel pointed to by coord
 * Colors are as such 0x00RRGGBB
 */

static bool	sphere_intersect(struct s_sphere *sp, t_vec3 org, t_vec3 dir, double *hit)
{
	double	a, b, c, discr, x_hit1, x_hit2;
	t_vec3	sphere_org_rel;

	sphere_org_rel = vec3_sub(org, sp->pos);
	a = vec3_dot(dir, dir);
	b = 2.0f * vec3_dot(sphere_org_rel, dir);
	c = vec3_dot(sphere_org_rel, sphere_org_rel) - pow(sp->diameter / 2, 2);
	discr = pow(b, 2) - (4 * a * c);
	if (discr < 0)
		return (false);
	x_hit1 = (-b + sqrt(discr)) / (2 * a);
	x_hit2 = (-b - sqrt(discr)) / (2 * a);
	if (x_hit1 >= 0 && (x_hit2 < 0 || x_hit1 < x_hit2))
		*hit = x_hit1;
	else if (x_hit2 >= 0 && (x_hit1 < 0 || x_hit2 < x_hit1))
		*hit = x_hit2;
	else
		return (false);
	return (true);
	/*t_vec3	hit = vec3_normalize(vec3_add(origin, vec3_mult_float(direction, x_hit)));

	ret.r = 255;
	ret.g = 0;
	ret.b = 0;
	//apply_ambient(win->scene->ambient, &ret);
	apply_light(win->scene->light, hit, &ret);
	return (ret);*/
}

bool	spheres_render_all(struct s_sphere *sp, t_vec3 org, t_vec3 dir, double *x)
{
	double	hit_near, hit;
	bool	has_hit;

	has_hit = false;
	hit_near = INFINITY;
	while (sp)
	{
		if (sphere_intersect(sp, org, dir, &hit) && hit < hit_near)
		{
			hit_near = hit;
			has_hit = true;
		}
		sp = sp->next_sphere;
	}
	if (has_hit)
		*x = hit_near;
	return (has_hit);
}
