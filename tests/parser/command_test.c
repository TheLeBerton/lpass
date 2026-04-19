#include "structures.h"
#include "core.h"

#include <criterion/criterion.h>
#include <unistd.h>

Test( parse_args_command_command, valid_init ) {
	t_args	args;
	char	*argv[] = { "lpass", "init", NULL };
	int	argc = 2;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_OK );
	cr_assert( args.cmd == LPASS_CMD_INIT );
	cr_assert_null( args.argument );
}

Test( parse_args_command_command, valid_list ) {
	t_args	args;
	char	*argv[] = { "lpass", "list", NULL };
	int	argc = 2;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_OK );
	cr_assert( args.cmd == LPASS_CMD_LIST );
	cr_assert_null( args.argument );
}

Test( parse_args_command_command, valid_add ) {
	t_args	args;
	char	*argv[] = { "lpass", "add", NULL };
	int	argc = 2;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_OK );
	cr_assert( args.cmd == LPASS_CMD_ADD );
	cr_assert_null( args.argument );
}

Test( parse_args_command, invalid_argument_single ) {
	t_args	args;
	char	*argv[] = { "lpass", "hello", NULL };
	int	argc = 2;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_ERR_ARGS_INVALID );
	cr_assert( args.cmd == LPASS_CMD_UNKNOWN );
	cr_assert_null( args.argument );
}

Test( parse_args_command, invalid_argument_multiple ) {
	t_args	args;
	char	*argv[] = { "lpass", "hello", "world", NULL };
	int	argc = 3;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_ERR_ARGS_INVALID );
	cr_assert( args.cmd == LPASS_CMD_UNKNOWN );
	cr_assert_null( args.argument );
}

Test( parse_args_command, uppercase_format ) {
	t_args	args;
	char	*argv[] = { "lpass", "ADD", NULL };
	int	argc = 2;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_OK );
	cr_assert( args.cmd == LPASS_CMD_ADD );
	cr_assert_null( args.argument );
}

