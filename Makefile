NAME = pipex
NAME_BONUS = pipex_bonus

SRCS	=	pipex.c\
			pipex_utils.c
			
SRCS_BONUS	= src_bonus/pipex_bonus.c\
				src_bonus/pipex_utils_bonus.c\
				src_bonus/here_doc_bonus.c

OBJS	= ${SRCS:.c=.o}

OBJS_BONUS 	= ${SRCS_BONUS:.c=.o}

LIBFT = ./libft
LIBPF = ./printf

HEADERS = -I ./includes
LIBS	= ${LIBFT}/libft.a ${LIBPF}/libftprintf.a

FLAGS	= -g -Wall -Wextra -Werror 

RM		= rm -f

all: libs ${NAME}

bonus: libs ${NAME_BONUS}

libs:
	@${MAKE} -C ${LIBFT}
	@${MAKE} -C ${LIBPF}

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${OBJS} ${LIBS} ${HEADERS} -o ${NAME}

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(FLAGS) $(OBJS_BONUS) ${LIBS} ${HEADERS} -o $(NAME_BONUS)

clean:
	@${RM} ${OBJS} $(OBJS_BONUS)
	@${MAKE} -C ${LIBFT} clean
	@${MAKE} -C ${LIBPF} clean

fclean: clean
	@${RM} ${NAME} $(NAME_BONUS)
	@${MAKE} -C ${LIBFT} fclean
	@${MAKE} -C ${LIBPF} fclean

re: fclean all

.PHONY: all, clean, fclean, re, bonus