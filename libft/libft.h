/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:13:50 by hdupire           #+#    #+#             */
/*   Updated: 2023/11/26 04:54:46 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/syscall.h>
# include <time.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_strcmp(const char *s1, const char *s2);

#endif
