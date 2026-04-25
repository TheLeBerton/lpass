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

void	error_handler_init( t_lpass_error err ) {
	if ( err == LPASS_ERR_ALREADY_EXISTS ) {
		fprintf( stderr, "[ ERROR ]: vault already exists\n" );
		return ;
	}
	if ( err == LPASS_ERR_ARGS_INVALID ) {
		fprintf( stderr, "[ ERROR ]: passwords do not match\n" );
		return ;
	}
	if ( err == LPASS_ERR_NULL ) {
		fprintf( stderr, "[ ERROR ]: input cannot be empty\n" );
		return ;
	}
	if ( err == LPASS_ERR_MEMORY ) {
		fprintf( stderr, "[ ERROR ]: memory allocation or crypto_pwhash failed\n" );
		return ;
	}
}

void	error_handler_copy( t_lpass_error err ) {
	if ( err == LPASS_ERR_MEMORY ) { 
		fprintf( stderr, "[ ERROR ]: memory allocation or crypto_pwhash failed\n" );
		return ;
	}
	if ( err == LPASS_ERR_NULL ) { 
		fprintf( stderr, "[ ERROR ]: vault or label is NULL\n" );
		return ;
	}
	if ( err == LPASS_WARN_NOT_FOUND ) { 
		fprintf( stderr, "[ ERROR ]: label was not found\n" );
		return ;
	}
}

void	error_handler_delete( t_lpass_error err ) {
	if ( err == LPASS_ERR_MEMORY ) { 
		fprintf( stderr, "[ ERROR ]: memory allocation or crypto_pwhash failed\n" );
		return ;
	}
	if ( err == LPASS_ERR_NULL ) { 
		fprintf( stderr, "[ ERROR ]: vault or label is NULL\n" );
		return ;
	}
	if ( err == LPASS_WARN_NOT_FOUND ) { 
		fprintf( stderr, "[ ERROR ]: label was not found\n" );
		return ;
	}
}

