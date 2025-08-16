NAME = minishell

CC = cc -Wall -Wextra -Werror -g

INCLUDES = -Iinclude -Ilibft

LIBFT_DIR = ./exec/libft
LIBFT = ./exec/libft/libft.a

FILES = cmd.c exec/built.c exec/exit.c exec/utils.c exec/checks.c exec/free.c \
		exec/utils_lst.c exec/execution.c exec/redir.c exec/heredoc.c\
		exec/signal.c \
		minishell.c \

OBJS = ${FILES:.c=.o}

%.o: %.c
	@${CC} ${INCLUDES} -c $< -o $@ > /dev/null

${NAME}: ${OBJS} ${LIBFT}
	@${CC} ${OBJS} $(LIBFT) -lreadline -o ${NAME}
	@echo "minishell compiled"

${LIBFT}:
	@make -s -C $(LIBFT_DIR)
	@echo "libft compiled"

all: ${NAME}

clean:
	@rm -f ${OBJS}
	@make -C $(LIBFT_DIR) clean > /dev/null
	@echo "object files got cleaned"

fclean: clean
	@rm -f ${NAME}
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@echo "everything cleaned"

re: fclean all

#compile with make val for flags
val: all clean
		valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=/put.ur.pwd/val.supp ./minishell

.PHONY: all clean fclean re
