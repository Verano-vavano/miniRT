/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:13:50 by hdupire           #+#    #+#             */
/*   Updated: 2023/11/27 18:54:58 by hdupire          ###   ########.fr       */
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

char		*get_next_line(int fd);

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strchr_int(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*free_buffers(char *buf1, ...);
size_t		ft_strlen(const char *s);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strndup(const char *s, size_t len);

#endif
