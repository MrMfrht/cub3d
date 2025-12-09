SCR		=	get_next_line_utils.c\
			get_next_line.c\
			scr/parsing/get_input.c\
			scr/parsing/check.c\
			scr/parsing/get_texture.c\
			scr/parsing/utils.c\
			scr/parsing/get_map.c\
			scr/parsing/get_rectangle.c\
			scr/parsing/validation/validate.c\
			scr/parsing/validation/validate_utils.c\
			scr/parsing/validation/validate_utils2.c\
			scr/after_parsing/init_map_player.c\
			scr/after_parsing/raycasting1.c\
			scr/after_parsing/raycasting2.c\
			scr/after_parsing/raycasting3.c\
			scr/render/key_press.c\
			scr/render/render.c\
			scr/render/free_cub.c\
			scr/render/init_utils/init_mlx.c\
			scr/render/init_utils/init_mlx2.c\
			scr/render/init_utils/init_cub.c\
			scr/render/player.c\
			scr/main.c\

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