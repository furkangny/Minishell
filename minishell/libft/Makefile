CC = gcc
functions = ft_is*.c ft_str*.c ft_mem*.c ft_bzero.c ft_to*.c ft_atoi.c \
ft_calloc.c ft_substr.c ft_split.c ft_itoa.c ft_put*.c
objs = ft_*.o
flag = -Wall -Werror -Wextra -c
NAME = libft.a
extra = ft_lst*.c


all: ${NAME}

${NAME}:
	@${CC} ${flag} ${functions}
	@ar rc ${NAME} ${objs}

bonus:
	@${CC} ${flag} ${functions} ${extra}
	@ar rc ${NAME} ${objs}

clean:
	@rm -f ${objs}

fclean: clean
	@rm -f ${NAME}

re: fclean all