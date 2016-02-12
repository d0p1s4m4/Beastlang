CC	= gcc
RM	= rm -f

CFLAGS	+= -ansi -pedantic -Wall -Werror -Wextra -g -ggdb
LDFLAGS	+=

NAME	= beast
SRCS	= main.c \
		error.c \
		lexer.c \
		utils.c \
		parser.c \
		context.c \
		eval.c \
		builtin.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 
