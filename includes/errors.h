/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:09:49 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 14:27:31 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "libft.h"
# include "render.h"

void	print_error(char *error);

bool	already_set_err(char set);
bool	invalid_range_err(char *set, char *lb, char *ub);
bool	too_many_args_war(char *set, char *req);
bool	malloc_err(char *set);

bool	float_convert_err(char c);
bool	float_too_many_digits(char c);

void	vec3_number_err(char *arg, char **xyz);
void	vec3_arg_err(char *arg, char **xyz);

bool	parsing_err(int argc, char **argv);

bool	parsing_err(int argc, char **argv);

#endif
