CFLAGS =			-Wall -Wextra -Werror -g -fsanitize=address

HDRS =				minirt.h

HDRS_DIR =			./includes/

CC =				cc

#BONUSDIR =			bonus/

#BONUS =				$(addprefix ${BONUSDIR}, minirt)

RM =				rm -rf

NAME =				minirt

SRC =				main.c parser.c get_next_line_utils_bonus.c get_next_line_bonus.c\
					utils.c utils2.c ./vector/vector_utils.c

SRC_DIR =			./src/

HEADERS =			$(addprefix ${HDRS_DIR}, ${HDRS})

SOURCES =			$(addprefix ${SRC_DIR}, ${SRC})

BUILDIR = 			./obj/

BUILDIRS =			echo/ cd/ env/ pwd/ utils/ pipex/ exec/ parser/ export/ exit/ libft/

BLDRS =				$(addprefix ${BUILDIR}, ${BUILDIRS})

OBJS =				$(addprefix ${BUILDIR}, ${SRC:.c=.o})

LIBFT_NAME =		libft.a

LIBFTDIR =			./libft/

LIBFT =				$(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

MLX_NAME =			libmlx.a

MLXDIR =			./mlx_linux/

MLX =				$(addprefix ${MLXDIR}, ${MLX_NAME})

INCLUDE = 			-I./mlx_linux -I./includes -I./libft

# LIBS = 				-L./mlx/ -lmlx -lm -L./libft/ -lft -framework OpenGL -framework AppKit

LIBS =				-L./mlx_linux -L/usr/lib -lXext -lX11 -lm -Imlx -L./libft -lft

.PHONY:				clean all fclean re

all:				${BUILDIR} ${BLDRS} ${LIBFT} ${MLX} ${NAME}

${LIBFT}:
					${MAKE} -C ${LIBFTDIR}

${MLX}:
					${MAKE} -C ${MLXDIR}

${NAME}:			${HEADERS} Makefile ${SOURCES}
					${CC} ${INCLUDE} ${CFLAGS} ${SOURCES} ${LIBS} ${MLX} -o $@

${BUILDIR}:
					mkdir -p $@

${BLDRS}:
					mkdir -p $@

${BUILDIR}%.o:		${SRC_DIR}%.c ${HEADERS} Makefile
					${CC} ${INCLUDE} -c ${CFLAGS} $< -o $@
#
#bonus:				${BONUS}
#
#${BONUS}:
#					${MAKE} -C ${BONUSDIR}

clean:
					#${MAKE} clean -C ${BONUSDIR}
					${MAKE} clean -C ${LIBFTDIR}
					${MAKE} clean -C ${MLXDIR}
					${RM} ${BUILDIR}

fclean:				clean
					${MAKE} fclean -C ${LIBFTDIR}
					#${MAKE} fclean -C ${BONUSDIR}
					${RM} ${NAME}

re:					fclean all

