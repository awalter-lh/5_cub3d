# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 20:51:15 by nbeaufil          #+#    #+#              #
#    Updated: 2023/07/09 05:14:28 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRCS	=	close_window.c				\
			cub3d.c						\
			event.c						\
			image.c						\
			minimap.c					\
			ray.c						\
			wall_color.c				\
			xpm_parser/mat_filling.c	\
			xpm_parser/parser.c			\
			xpm_parser/parser_utils.c

OBJS	=	${SRCS:.c=.o}

FLAGS	=	-Wall -Wextra -Werror

LIBS	=	minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm -g3

.c.o:
	gcc ${FLAGS} -c $< -o ${<:.c=.o}

all	:	${NAME}

${NAME}	:	${OBJS}
	make all -C parsing
	gcc ${FLAGS} ${OBJS} ${LIBS} parsing/libparsing.a -o ${NAME}

clean	:
	make clean -C parsing
	rm -f ${OBJS}

fclean	:	clean
	make fclean -C parsing
	rm -f ${NAME}

re	:	fclean	all

.PHONY: all clean fclean re

.SILENT:
