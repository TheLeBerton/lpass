#include "structures.h"
#include "core.h"

#include <criterion/criterion.h>
#include <unistd.h>

Test( parse_args_argc, not_enough_args ) {
	t_args	args;
	char	*argv[] = { "lpass", NULL };
	int	argc = 1;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_ERR_ARGS_MISSING );
}

Test( parse_args_argc, too_many_args ) {
	t_args	args;
	char	*argv[] = { "lpass", "add", "foul", "github", NULL };
	int	argc = 4;
	t_lpass_error	err = parse_args( argc, argv, &args );
	cr_assert( err == LPASS_ERR_ARGS_INVALID );
}

