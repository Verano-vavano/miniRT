/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   latof_errs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:06:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/11/30 23:10:13 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

bool	float_convert_err(char c)
{
	write(2, &c, 1);
	write(2, ": Invalid char in float conversion\n", 35);
	return (false);
}

bool	float_too_many_digits(char c)
{
	write(2, &c, 1);
	write(2, ": Too many digits in float conversion\n", 38);
	return (false);
}
