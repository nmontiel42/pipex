NAME = libftprintf.a

SOURCE = ft_decient.c\
		ft_hexa.c\
		ft_pointer.c\
		ft_printf.c\
		ft_putchar.c\
		ft_string.c\
		ft_unsigned.c\
		
OBJ = $(SOURCE:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIB = ar rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(LIB) $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re all clean fclean