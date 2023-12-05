/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:22:28 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/03 15:42:16 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_valid_num(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
		i++;
	return (s[i] == '\0');
}
