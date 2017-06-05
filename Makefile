CC	= clang
RM	= rm -f

CFLAGS	+= -ansi -pedantic -Wall -Werror -Wextra -Os -I include
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
OBJS	= $(addprefix src/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

test:
	$(MAKE) -f test.makefile

clean:
	$(RM) $(OBJS)
	$(MAKE) -f test.makefile clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -f test.makefile fclean

re: fclean all

.PHONY: all clean fclean re test
