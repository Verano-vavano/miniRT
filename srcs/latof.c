/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   latof.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:45:39 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 15:40:33 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errors.h"
#include <math.h>

static bool	float_check_arg(char *arg)
{
	short	d_count;

	d_count = 0;
	while (*arg == '+' || *arg == '-')
		arg++;
	while (*arg && *arg != '.')
	{
		if (*arg < '0' || *arg > '9')
			return (float_convert_err(*arg));
		arg++;
		d_count++;
		if (d_count > 5)
			return (float_too_many_digits(*arg));
	}
	arg += (*arg == '.');
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
			return (float_convert_err(*arg));
		arg++;
	}
	return (true);
}

static float	atof_convert(char *arg)
{
	float	ret;
	bool	dec;
	int		decimal_point;
	int		iter;

	iter = 0;
	ret = 0;
	dec = false;
	decimal_point = ft_strchr_int(arg, '.');
	while (arg[iter] && iter - decimal_point < 5)
	{
		if (iter == decimal_point && !dec)
		{
			arg++;
			dec = true;
			continue ;
		}
		ret += ((arg[iter] - '0') * (pow(10, decimal_point - iter - 1)));
		iter++;
	}
	return (ret);
}

static char	*cut_useless(char *arg)
{
	size_t	n;
	size_t	decimal_point;

	while (*arg && (*arg == '-' || *arg == '+'))
		arg++;
	while (*arg && *arg == '0')
		arg++;
	n = ft_strlen(arg) - 1;
	decimal_point = ft_strchr_int(arg, '.');
	while (*arg && n > decimal_point && arg[n] == '0')
		n--;
	arg[n + 1] = '\0';
	return (arg);
}

// little_atof does a simple conversion from a char* to a float.
// Opposed to a regular atof, it only converts numbers if they have
// less than 6 digits in the base part and 6 digits in the decimal
// part. For example, it converts numbers as such -35627.65321.
// For this project, no user should be able to input larger numbers.
// Float limits being very unstable and hard to manage, it was
// logical to limits the bounds to more reasonable standards.
// An error in the conversion will result in the following value:
// 111111f, so 111111f > 99999f which would be the largest number.
float	little_atof(char *arg)
{
	short	neg;

	neg = 1;
	while (*arg && (*arg == '+' || *arg == '-'))
	{
		neg *= (-1 * (*arg == '-') + 1 * (*arg == '+'));
		arg++;
	}
	arg = cut_useless(arg);
	if (!float_check_arg(arg))
		return (FLOAT_ERR);
	return (atof_convert(arg) * neg);
}
