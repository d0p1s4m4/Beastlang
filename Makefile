CC	?= gcc
AR	= ar
RM	= rm -f

CFLAGS	+= -ansi -pedantic -Werror -Wall -Wextra
LDFLAGS	+=

SRCDIR	= src

all: beastlang

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

include src/build.mk

clean:
	$(RM) $(BIN_OBJS) $(LIB_OBJS)

fclean: clean
	$(RM) beastlang libbeast.a

re: fclean all

.PHONY: all clean fclean re