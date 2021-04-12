
LIB_SRCS	= dummy.c
LIB_OBJS	= $(addprefix $(SRCDIR)/libbeast/, $(LIB_SRCS:.c=.o))

libbeast.a: $(LIB_OBJS)
	$(AR) -rc $@ $^