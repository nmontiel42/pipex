NAME = pipex

SRCS	=	pipex.c\
			pipex_utils.c
			

OBJS	= ${SRCS:.c=.o}

LIBFT = ./libft
LIBPF = ./printf

HEADERS = -I ./includes
LIBS	= ${LIBFT}/libft.a ${LIBPF}/libftprintf.a

FLAGS	= -Wall -Wextra -Werror 

RM		= rm -f

all: libs ${NAME}

libs:
	@${MAKE} -C ${LIBFT}
	@${MAKE} -C ${LIBPF}

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${OBJS} ${LIBS} ${HEADERS} -o ${NAME}

clean:
	@${RM} ${OBJS}
	@${MAKE} -C ${LIBFT} clean
	@${MAKE} -C ${LIBPF} clean

fclean: clean
	@${RM} ${NAME}
	@${MAKE} -C ${LIBFT} fclean
	@${MAKE} -C ${LIBPF} fclean

re: fclean all

.PHONY: all, clean, fclean, re