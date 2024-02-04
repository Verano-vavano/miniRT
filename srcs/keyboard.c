/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:38:20 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/04 15:57:35 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

static char	get_kb(int fd)
{
	int		r;
	char	c;
	char	readed[1024];
	char	**splited;

	r = read(fd, readed, 1023);
	readed[r] = 0;
	splited = ft_split(readed, '\n');
	r = 0;
	c = 'q';
	while (splited[r])
	{
		if (ft_strncmp(splited[r], "KEYMAP=\"", 8) == 0)
		{
			if (ft_strncmp(splited[r] + 8, "fr", 2) == 0)
				c = 'a';
			break ;
		}
		r++;
	}
	free_char_etoile_etoile(splited);
	close(fd);
	return (c);
}

void	keyboard_conf(t_window *window)
{
	int	fd;

	fd = open("/etc/vconsole.conf", O_RDONLY);
	if (fd == -1)
		window->keyboard = 'a';
	else
		window->keyboard = get_kb(fd);
}
