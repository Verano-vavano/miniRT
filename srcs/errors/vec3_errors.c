/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:00:21 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/07 14:42:41 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "scene.h"

void	vec3_number_err(char *arg, char **xyz)
{
	write(2, "Error\n", 6);
	write(2, "[VEC3] Invalid number of arguments. 3 required : ", 49);
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
	free_char_etoile_etoile(xyz);
}

void	vec3_arg_err(char *arg, char **xyz)
{
	write(2, "Error\n", 6);
	write(2, "[VEC3] Invalid argument : ", 26);
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
	free_char_etoile_etoile(xyz);
}
