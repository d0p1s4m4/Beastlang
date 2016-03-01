CC	= clang
COV	= lcov
RM	= rm -f

NAME	= test

CFLAGS	= -ansi -pedantic -Wall -Werror -Wextra -g -fprofile-arcs -ftest-coverage
LDFLAGS	= --coverage

SRCS	= main.c \
		error.c \
		lexer.c \
		utils.c \
		parser.c \
		context.c \
		eval.c \
		builtin.c
OBJS	= $(SRCS:.c=.o)
COVS	= $(SRCS:.c=.gcda) $(SRCS:.c=.gcno)

all: $(NAME) coverage
	./$(NAME) *.666
	genhtml cov.info -o output

coverage:
	lcov --directory . \
		--base-directory . \
		--gcov-tool llvm-cov \
		--capture -o cov.info

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(COVS)

fclean: clean
	$(RM) $(NAME)
	$(RM) -r output
	$(RM) cov.info

re: fclean all

.PHONY: all clean fclean re
