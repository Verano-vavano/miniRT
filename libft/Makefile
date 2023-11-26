# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 09:06:31 by hdupire           #+#    #+#              #
#    Updated: 2023/11/26 04:53:56 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = 
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
