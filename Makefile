NAME 		= lpass
NAMETEST	= test_runner
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I./includes $(shell pkg-config --cflags libsodium)
LDFLAGS		= $(shell pkg-config --libs libsodium)
TESTFLAGS	= $(shell pkg-config --cflags --libs criterion)

SRCS		= srcs/utils.c \
			  srcs/vault/entry_helpers.c \
			  srcs/vault/entry.c \
			  srcs/vault/vault.c \
			  srcs/vault/vault_helpers.c \
			  srcs/core/crypto.c \
			  srcs/core/parser.c \
			  srcs/core/error_handler.c \
			  srcs/commands/init.c 

TESTS		= tests/entry/create_test.c \
			  tests/entry/get_test.c \
			  tests/entry/search_test.c \
			  tests/entry/update_test.c \
			  tests/entry/delete_test.c \
			  tests/vault/save_test.c \
			  tests/vault/load_test.c \
			  tests/parser/argc_test.c \
			  tests/parser/argument_test.c \
			  tests/parser/command_test.c \
			  tests/crypto/derive_key_test.c

OBJSDIR		= objs
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
MAINOBJ		= $(OBJSDIR)/main.o

RM			= rm -f
MKDIR		= mkdir -p

all: $(OBJS) $(MAINOBJ)
	$(CC) $(CFLAGS) $(OBJS) $(MAINOBJ) $(LDFLAGS) -o $(NAME)

$(OBJSDIR)/%.o: %.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAINOBJ)

fclean: clean
	$(RM) $(NAME) $(NAMETEST)

re: fclean all

test: $(OBJS)
	$(CC) $(CFLAGS) $(TESTS) $(OBJS) $(TESTFLAGS) $(LDFLAGS) -o $(NAMETEST)
	@printf "\n======== ENTRY ========\n"
	@printf "\n******** entry_create ********\n\n"
	-@./$(NAMETEST) --filter "entry_create/*"
	@printf "\n******** entry_get ********\n\n"
	-@./$(NAMETEST) --filter "entry_get/*"
	@printf "\n******** entry_search ********\n\n"
	-@./$(NAMETEST) --filter "entry_search/*"
	@printf "\n******** entry_update ********\n\n"
	-@./$(NAMETEST) --filter "entry_update/*"
	@printf "\n******** entry_delete ********\n\n"
	-@./$(NAMETEST) --filter "entry_delete/*"
	@printf "\n\n======== VAULT ========\n"
	@printf "\n******** vault_save ********\n\n"
	-@./$(NAMETEST) --filter "vault_save/*"
	@printf "\n******** vault_load ********\n\n"
	-@./$(NAMETEST) --filter "vault_load/*"
	@printf "\n\n======== PARSER ========\n"
	@printf "\n******** parser_args_argc ********\n\n"
	-@./$(NAMETEST) --filter "parse_args_argc/*"
	@printf "\n******** parser_args_command ********\n\n"
	-@./$(NAMETEST) --filter "parse_args_command/*"
	@printf "\n******** parser_args_argument ********\n\n"
	-@./$(NAMETEST) --filter "parse_args_argument/*"
	@printf "\n\n======== CRYPTO ========\n"
	@printf "\n******** derive_key ********\n\n"
	-@./$(NAMETEST) --filter "derive_key/*"
