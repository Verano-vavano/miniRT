/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:41:35 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/05 01:19:21 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_hit	trace(t_scene *scene, t_ray ray, t_lform *lform, bool pl)
{
	t_lform	t_lf;
	t_hit	hit;
	t_hit	t_hit;

	hit.has_hit = false;
	hit.t = INFINITY;
	if (sp_render(scene->spheres, ray, &t_hit, lform))
	{
		hit = t_hit;
		hit.has_hit = true;
	}
	if (pl && pl_render(scene->planes, ray, &t_hit, &t_lf) && t_hit.t < hit.t)
	{
		hit = t_hit;
		*lform = t_lf;
		hit.has_hit = true;
	}
	t_hit.t = INFINITY;
	if (cyl_render(scene->cyl, ray, &t_hit, &t_lf) && t_hit.t < hit.t)
	{
		hit = t_hit;
		*lform = t_lf;
		hit.has_hit = true;
	}
	return (hit);
}

t_color	cast_ray(t_window *window, t_ray ray, int ray_num)
{
	t_scene		*scene;
	t_hit		hit;
	t_color		ret;
	t_lcont		contr;
	t_lform		last_form;

	init_lgt_contr(&contr);
	scene = window->scene;
	last_form.addr = NULL;
	hit.shade = NULL;
	hit = trace(scene, ray, &last_form, true);
	if (hit.t > (NEAR_CLIP * (ray_num == 0))
		&& hit.t < FAR_CLIP && last_form.addr != NULL)
	{
		if (hit.shade && hit.shade->reflect && ray_num < MAX_REFLECTION)
			reflect_color(window, &hit, ray.dir, ray_num);
		ambient_lighting(scene->ambient, &(contr.amb_contr), hit.color);
		dir_lighting(scene, &hit, &(contr.lgt_contr));
		sph_lighting(scene, &hit, &(contr.lgt_contr));
	}
	ret.r = (fmin(1.f, contr.lgt_contr.r + contr.amb_contr.r)) * 255;
	ret.g = (fmin(1.f, contr.lgt_contr.g + contr.amb_contr.g)) * 255;
	ret.b = (fmin(1.f, contr.lgt_contr.b + contr.amb_contr.b)) * 255;
	return (ret);
}

void	calculate_ray(t_ray *ray, t_window *window, t_vec2 *coord, float fov)
{
	ray->org = window->scene->camera.vp;
	ray->dir.x = (2.0f * (coord->x + 0.5f) / window->width - 1.0f)
		* window->aspect_ratio * tan(fov / 2);
	ray->dir.y = (1.0f - 2.0f * (coord->y + 0.5f) / window->height)
		* tan(fov / 2);
	ray->dir.z = 1;
	ray->dir = cam2world(window->cam, &ray->dir);
	ray->dir = vec3_normalize(ray->dir);
	return ;
}
