/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:19:54 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 14:51:59 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "errors.h"
#include "libft.h"

static bool	assign_color_struct(t_color *ret, char *arg, int color)
{
	int	converted_arg;
	int	end_signs;

	end_signs = 0;
	while (arg[end_signs] && (arg[end_signs] == '+' || arg[end_signs] == '-'))
		end_signs++;
	if (ft_strlen(arg + end_signs) > 3 || !is_valid_num(arg))
		return (false);
	converted_arg = ft_atoi(arg);
	if (converted_arg > 255 || converted_arg < 0)
		return (false);
	if (color == 0)
		ret->r = converted_arg;
	else if (color == 1)
		ret->g = converted_arg;
	else
		ret->b = converted_arg;
	return (true);
}

t_color	get_color(char *arg)
{
	t_color	ret;
	char	**rgb;
	int		i;

	ret.valid = false;
	rgb = ft_split(arg, ',');
	if (!rgb)
		return (ret);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3] != NULL)
	{
		vec3_number_err(arg, rgb);
		return (ret);
	}
	i = -1;
	while (++i < 3)
	{
		if (assign_color_struct(&ret, rgb[i], i) == false)
		{
			vec3_arg_err(rgb[i], rgb);
			return (ret);
		}
	}
	ret.valid = true;
	free_char_etoile_etoile(rgb);
	return (ret);
}

void	copy_color(t_color *col, uint8_t r, uint8_t g, uint8_t b)
{
	col->r = r;
	col->g = g;
	col->b = b;
	return ;
}

t_col01	copy_col_to_01(t_color col)
{
	t_col01	ret;

	ret.r = col.r / 255.f;
	ret.g = col.g / 255.f;
	ret.b = col.b / 255.f;
	return (ret);
}
