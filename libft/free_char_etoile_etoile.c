/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_char_etoile_etoile.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:12:18 by tcharanc          #+#    #+#             */
/*   Updated: 2023/12/01 22:43:26 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_char_etoile_etoile(char **truc)
{
	int	i;

	i = -1;
	while (truc[++i])
		free(truc[i]);
	free(truc);
}
