/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_intable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:18:02 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/03 15:47:29 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	atol_cmp(char *s, bool neg)
{
	long	val;

	val = ft_atol(s);
	if (neg)
		val *= (-1);
	return (val >= INT_MIN && val <= INT_MAX);
}

static long	check_ender(char *s)
{
	long	n;
	long	after;

	n = 0;
	while (s[n] && s[n] != '.')
		n++;
	if (!s[n])
		return (n);
	if (s[n] == '.')
		s++;
	after = n;
	while (s[after] == '0')
		after++;
	if (!s[after])
		return (n);
	return (-1);
}

// Whether or not a string can be atoied
bool	is_intable(char *s)
{
	static int	int_max_size;
	bool		neg;
	long		size;

	if (int_max_size == 0)
		int_max_size = get_int_size(INT_MAX);
	neg = false;
	while (*s && (*s == '+' || *s == '-'))
	{
		neg ^= (*s == '-');
		s++;
	}
	while (*s && *s == '0')
		s++;
	size = check_ender(s);
	if (size == -1)
		return (false);
	if (size < int_max_size)
		return (true);
	else if (size > int_max_size)
		return (false);
	else
		return (atol_cmp(s, neg));
}
