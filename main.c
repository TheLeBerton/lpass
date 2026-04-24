#include "structures.h"
#include "cli.h"
#include "commands.h"

#include <stdint.h>
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
	t_vault	vault = { 0 };
	err = handle_cmd( &vault, args );
	if ( err ) {
		fprintf( stderr, "[ ERROR ]: handle_cmd returned error [ %d ]\n", err );
		return ( err );
	}
	return ( EXIT_SUCCESS );
}
