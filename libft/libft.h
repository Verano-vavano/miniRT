/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:13:50 by hdupire           #+#    #+#             */
/*   Updated: 2024/02/03 22:48:58 by hdupire          ###   ########.fr       */
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
char		**ft_split(char const *s, char c);
void		free_char_etoile_etoile(char **truc);
bool		is_valid_num(char *s);
int		ft_atoi(const char *str);
long		ft_atol(const char *str);
int		get_int_size(int n);
bool		is_intable(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
