# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 20:51:15 by nbeaufil          #+#    #+#              #
#    Updated: 2023/07/08 23:21:10 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libparsing.a

SRCS	=	gnl/get_next_line.c			\
			gnl/get_next_line_utils.c	\
			parsing_utils.c				\
			parsing.c					\
			check_num.c					\
			utils.c						\
			parsing_ext.c				\
			extract_map.c				\
			extract_map_ext.c			\
			extract_inf.c				\
			lee_algo.c

OBJS	=	${SRCS:.c=.o}

FLAGS	=	-Wall -Wextra -Werror -g3

.c.o:
	gcc ${FLAGS} -c $< -o ${<:.c=.o}

all	:	${NAME}

${NAME}	:	${OBJS}
	ar rcs ${NAME} ${OBJS}
	ranlib ${NAME}

test	:	${NAME}
	gcc ${FLAGS} test.c ${NAME} -o test

clean	:
	rm -f ${OBJS}

fclean	:	clean
	rm -f ${NAME}
	rm -f test

re	:	fclean	all

.PHONY: all clean fclean re

.SILENT:
