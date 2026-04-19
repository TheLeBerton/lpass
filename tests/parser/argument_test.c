#include "structures.h"
#include "core.h"

#include <criterion/criterion.h>
#include <unistd.h>

Test( parse_args_argument, valid_get ) {
	t_args	args;
	char	*argv[] = { "lpass", "get", "github", NULL };
	int	argc = 3;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_OK );
	cr_assert( args.cmd == LPASS_CMD_GET );
	cr_assert_str_eq( args.argument, "github" );
	free( args.argument );
}

Test( parse_args_argument, valid_copy ) {
	t_args	args;
	char	*argv[] = { "lpass", "copy", "github", NULL };
	int	argc = 3;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_OK );
	cr_assert( args.cmd == LPASS_CMD_COPY );
	cr_assert_str_eq( args.argument, "github" );
	free( args.argument );
}

Test( parse_args_argument, valid_delete ) {
	t_args	args;
	char	*argv[] = { "lpass", "delete", "github", NULL };
	int	argc = 3;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_OK );
	cr_assert( args.cmd == LPASS_CMD_DEL );
	cr_assert_str_eq( args.argument, "github" );
	free( args.argument );
}

Test( parse_args_argument, missing_argument ) {
	t_args	args;
	char	*argv[] = { "lpass", "delete", "", NULL };
	int	argc = 3;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_ERR_ARGS_MISSING );
	cr_assert( args.cmd == LPASS_CMD_DEL );
	cr_assert_null( args.argument );
}

