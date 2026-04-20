#include "structures.h"
#include "core.h"
#include "commands.h"

#include <stdio.h>
#include <stdlib.h>


int main( int argc, char **argv ) {
	t_args			args;
	t_lpass_error	err;
	err = parse_args( argc , argv, &args );
	if ( err != LPASS_OK ) {
		error_handler_args( err );
		return ( err );
	}
	printf( "args.cmd: %d\n", args.cmd );
	printf( "args.argument: %s\n", args.argument );
	cmd_init();
	return ( EXIT_SUCCESS );
}
