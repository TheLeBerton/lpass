#include "structures.h"

#include <stdio.h>

static void	_print_usage() {
	fprintf( stderr, "[ USAGE ]: lpass <cmd> <argument>\n" );
	fprintf( stderr, "[ CMDS ] :\n" );
	fprintf( stderr, "	- init\n" );
	fprintf( stderr, "	- add\n" );
	fprintf( stderr, "	- list\n" );
	fprintf( stderr, "	- gen\n" );
	fprintf( stderr, "	- copy <label>\n" );
	fprintf( stderr, "	- delete <label>\n" );
}

void	error_handler_args( t_lpass_error err ) {
	if ( err == LPASS_ERR_MEMORY ) {
		fprintf( stderr, "[ ERROR ]: memory allocation failed\n" );
		return ;
	}
	if ( err == LPASS_ERR_ARGS_INVALID )
		fprintf( stderr, "[ ERROR ]: argument count bigger than 3 or unknown command\n" );
	else if ( err == LPASS_ERR_ARGS_MISSING )
		fprintf( stderr, "[ ERROR ]: argument count smaller than 2 or missing argument for <cmd>\n" );
	_print_usage();
}
