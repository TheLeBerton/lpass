#include "structures.h"
#include "cli.h"
#include "commands.h"

#include <stdlib.h>


int main( int argc, char **argv ) {
	t_args			args;
	t_lpass_error	err;
	err = parse_args( argc , argv, &args );
	if ( err != LPASS_OK ) {
		error_handler_args( err );
		return ( err );
	}
	t_vault	vault = { 0 };
	if ( args.cmd == LPASS_CMD_INIT ) {
		err = cmd_init( &vault );
		if ( err != LPASS_OK ) {
			error_handler_init( err );
			return ( err );
		}
	}
	return ( EXIT_SUCCESS );
}
