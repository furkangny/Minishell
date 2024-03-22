SRCS = main.c utils/doublepointer.c utils/doublepointer2.c signals.c parser/parser.c parser/parser2.c parser/parsercomplete.c path.c builtin/cd.c\
		builtin/pwd.c builtin/env.c builtin/export.c utils/errorcontrol.c pip.c execv.c builtin/unset.c builtin/exit.c\
		dollar/dollar.c redirections.c utils/execute.c parser/parser3.c utils/executeforred.c utils/quotesfunctions.c utils/redfunctions.c\
		utils/shellinit.c utils/freevarforwhile.c builtin/echo.c parser/handle_parser.c

CC = @gcc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
RM = @rm -rf

READLINE = readline

all: $(READLINE) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install

$(NAME):
	make -C libft/
	$(CC) -o $(NAME) $(CFLAGS) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline libft/libft.a $(SRCS)

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft/

clean:
	$(RM) readline-8.2 readline-8.2.tar.gz
	make clean -C libft/

re: fclean all
