#include "structures.h"
#include "cli.h"
#include "the_commands.h"

t_lpass_error	handle_cmd( t_vault *vault, t_args args ) {
	t_lpass_error	err;

	if ( args.cmd == LPASS_CMD_INIT ) {
		err = cmd_init( vault );
		if ( err != LPASS_OK ) {
			error_handler_init( err );
			return ( err );
		}
	}
	return ( LPASS_OK );
}
