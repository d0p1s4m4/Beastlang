include $(SRCDIR)/libbeast/build.mk

BIN_SRCS	= main.c
BIN_OBJS	= $(addprefix $(SRCDIR)/, $(BIN_SRCS:.c=.o))

beastlang: libbeast.a $(BIN_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
