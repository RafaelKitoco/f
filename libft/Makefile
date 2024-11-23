NAME		= libft.a
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
OBJ			= $(SRC:.c=.o)
SRC			= 	ft_calloc.c \
				ft_itoa.c \
				ft_memset.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_strcmp.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strdup.c \
				ft_substr.c \
				ft_isdigit.c \
				ft_strtrim.c \
				ft_atoi.c \
				ft_strchr.c \
				ft_fd_lines_counter.c \
				ft_err_msg.c \
				ft_isalpha.c \
				get_next_line.c \
				ft_strchrstr.c \
				ft_free_matriz.c \
				ft_isspace.c \
				ft_matrizdup.c \
				ft_matriz_big_line.c \
				ft_matrizlen.c \
				ft_bzero.c \
				ft_split.c \
				get_next_line_utils.c

all:		$(NAME)

$(NAME):	$(OBJ)
			ar rcs $@ $^

%.o:		%.c
			$(CC) $(FLAGS) -o $@ -c $<

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
