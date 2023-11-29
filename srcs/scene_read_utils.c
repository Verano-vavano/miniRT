/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_read_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:52:37 by hdupire           #+#    #+#             */
/*   Updated: 2023/11/28 15:39:38 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

char	*get_line_arg(char *line, int *adv)
{
	int	len;

	*adv = 0;
	while (*line == ' ')
	{
		line++;
		(*adv)++;
	}
	if (*line == '\n')
		return (NULL);
	len = 0;
	while (line[len] && line[len] != ' ' && line[len] != '\n')
		len++;
	(*adv) += len;
	return (ft_strndup(line, len));
}
