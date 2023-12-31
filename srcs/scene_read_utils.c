/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_read_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:52:37 by hdupire           #+#    #+#             */
/*   Updated: 2023/12/05 10:35:24 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "libft.h"

char	*get_line_arg(char *line, int *adv)
{
	int	len;

	if (adv)
		*adv = 0;
	while (*line == ' ')
	{
		line++;
		if (adv)
			(*adv)++;
	}
	if (*line == '\n')
		return (NULL);
	len = 0;
	while (line[len] && line[len] != ' ' && line[len] != '\n')
		len++;
	if (adv)
		(*adv) += len;
	return (ft_strndup(line, len));
}
