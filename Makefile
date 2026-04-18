NAME 		= lpass
NAMETEST	= test_runner
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I./includes
TESTFLAGS	= $(shell pkg-config --cflags --libs criterion)

SRCS		= srcs/utils.c \
			  srcs/vault/entry_helpers.c \
			  srcs/vault/entry.c

TESTS		= tests/entry/create_test.c \
			  tests/entry/get_test.c \
			  tests/entry/search_test.c \
			  tests/entry/update_test.c

OBJSDIR		= objs
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
MAINOBJ		= $(OBJSDIR)/main.o

RM			= rm -f
MKDIR		= mkdir -p

all: $(OBJS) $(MAINOBJ)
	$(CC) $(CFLAGS) $(OBJS) $(MAINOBJ) -o $(NAME)

$(OBJSDIR)/%.o: %.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAINOBJ)

fclean: clean
	$(RM) $(NAME) $(NAMETEST)

re: fclean all

test: $(OBJS)
	$(CC) $(CFLAGS) $(TESTS) $(OBJS) $(TESTFLAGS) -o $(NAMETEST)
	./$(NAMETEST)
