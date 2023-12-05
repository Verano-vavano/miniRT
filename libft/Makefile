# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 09:06:31 by hdupire           #+#    #+#              #
#    Updated: 2023/12/03 15:30:15 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_bzero.c ft_calloc.c ft_strchr_int.c ft_strcmp.c ft_strjoin.c free_buffers.c ft_strlen.c get_next_line.c ft_strndup.c ft_split.c free_char_etoile_etoile.c is_valid_num.c ft_atoi.c ft_atol.c is_intable.c get_int_size.c
DEST = $(SRCS:.c=.o)

all: ${NAME}

.c.o:
	@gcc -Wall -Wextra -Werror -c -I ./ $< -o ${<:.c=.o}

${NAME} : ${DEST}
	@ar crs ${NAME} ${DEST}

clean:
	rm -f ${DEST} ${DEST_BONUS}

fclean: clean
	rm -f ${NAME}

re: fclean all
