
CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC =	ft_strcmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c	\
		ft_strlen.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c	\
		ft_bzero.c ft_memset.c ft_memcpy.c ft_memchr.c ft_memmove.c	\
		ft_atoi.c ft_calloc.c ft_memcmp.c ft_strdup.c ft_strjoin.c \
		ft_substr.c	ft_strtrim.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_itoa.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
%.o : %.c libft.h
	$(CC) $(FLAGS) -c $< -o $@

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re
