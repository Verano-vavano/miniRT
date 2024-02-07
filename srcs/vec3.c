/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:28:46 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 14:25:21 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "errors.h"
#include "libft.h"

static bool	assign_vec3(t_vec3 *ret, char *coord, int index, bool smallest)
{
	double	f_coord;

	f_coord = little_atof(coord);
	if (smallest && (f_coord < -1 || f_coord > 1))
		return (false);
	if (index == 0)
		ret->x = f_coord;
	else if (index == 1)
		ret->y = f_coord;
	else
		ret->z = f_coord;
	return (true);
}

t_vec3	get_coord_vec3(char *arg, bool smallest)
{
	t_vec3	ret;
	int		current;
	char	**xyz;

	ret.valid = false;
	xyz = ft_split(arg, ',');
	if (!xyz)
		return (ret);
	if (!xyz[0] || !xyz[1] || !xyz[2] || xyz[3])
	{
		vec3_number_err(arg, xyz);
		return (ret);
	}
	current = -1;
	while (++current < 3)
	{
		if (!assign_vec3(&ret, xyz[current], current, smallest))
		{
			vec3_arg_err(xyz[current], xyz);
			return (ret);
		}
	}
	ret.valid = (ret.x < FLOAT_ERR && ret.y < FLOAT_ERR && ret.z < FLOAT_ERR);
	free_char_etoile_etoile(xyz);
	return (ret);
}
