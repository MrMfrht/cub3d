SCR		=	get_next_line_utils.c\
			get_next_line.c\
			parsing/get_input.c\
			parsing/check.c\
			parsing/get_texture.c\
			parsing/utils.c\
			parsing/get_map.c\
			parsing/get_rectangle.c\
			parsing/validation/validate.c\
			after_parsing/init_map_player.c\
			after_parsing/raycasting1.c\
			after_parsing/raycasting2.c\
			after_parsing/raycasting3.c\
			render/key_press.c\
			render/render.c\
			render/free_cub.c\
			render/init_utils/init_mlx.c\
			render/player.c\
			main.c\

OBJS	=	${SCR:.c=.o}

NAME	=	cub3D

LIBFTDIR = libft/
MINILIBXDIR = minilibx-linux/

RM		=	rm -f
GCC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g

LIBFTFLAGS = -L ${LIBFTDIR} -lft
MINILIBXFLAGS = -L ${MINILIBXDIR}  -lmlx -lXext -lX11 -lm -lz
INCLUDE = ${LIBFTFLAGS} ${MINILIBXFLAGS}

all:	${NAME}

.c.o:	
		${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C ${LIBFTDIR}
			${GCC} ${CFLAGS} -o ${NAME} ${OBJS} ${INCLUDE}
clean:		
			${RM} ${OBJS}
			@cd ${LIBFTDIR} && $(MAKE) clean

fclean:		clean
			${RM} ${NAME}
			@cd ${LIBFTDIR} && $(MAKE) fclean

re:			fclean all