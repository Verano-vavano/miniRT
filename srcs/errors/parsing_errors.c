/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:21:45 by tcharanc          #+#    #+#             */
/*   Updated: 2023/12/16 18:10:26 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"

bool	parsing_err(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 1)
	{
		printf("Error\nNeed at least one argument\n");
		return (1);
	}
	i = 2;
	while (argv[i])
	{
		if (access(argv[i], R_OK) == -1)
		{
			printf("Error\nCould not access file\n");
			return (1);
		}
		j = ft_strlen(argv[i]);
		if (j < 3 || ft_strcmp(&argv[i][j - 3], ".rt"))
		{
			printf("Error\nfile is not a valid rt file\n");
			return (1);
		}
	}
	return (0);
}
