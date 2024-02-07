/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:15:47 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 14:42:05 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

bool	already_set_err(char set)
{
	write(2, "Error\n", 6);
	write(2, "[", 1);
	write(2, &set, 1);
	write(2, "] ALREADY SET\n", 14);
	return (false);
}

bool	invalid_range_err(char *set, char *lb, char *ub)
{
	write(2, "Error\n", 6);
	write(2, "[", 1);
	write(2, set, ft_strlen(set));
	write(2, "] BOUNDS ERROR (must be between ", 32);
	write(2, lb, ft_strlen(lb));
	write(2, " and ", 5);
	write(2, ub, ft_strlen(ub));
	write(2, ")\n", 2);
	return (false);
}

bool	too_many_args_war(char *set, char *req)
{
	write(2, "Error\n", 6);
	write(2, "[", 1);
	write(2, set, ft_strlen(set));
	write(2, "] WARNING : TOO MANY ARGUMENTS (", 32);
	write(2, req, ft_strlen(req));
	write(2, " required)\n", 11);
	return (false);
}

bool	malloc_err(char *set)
{
	write(2, "Error\n", 6);
	write(2, "[", 1);
	write(2, set, ft_strlen(set));
	write(2, "] MEMORY ALLOCATION ERROR\n", 26);
	return (false);
}

void	print_error(char *error)
{
	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}
