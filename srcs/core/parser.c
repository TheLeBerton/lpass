#include "structures.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static t_lpass_error	_handle_command( char *arg, t_args *args ) ;
static t_lpass_error	_add_arg_to_cmd( t_args *args, char *arg ) ;
static int				_needs_arg( t_command cmd ) ;

t_lpass_error	parse_args( int argc, char **argv, t_args *args ) {
	args->argument = NULL;
	if ( argc < 2 )
		return ( LPASS_ERR_ARGS_MISSING );
	if ( argc > 3 )
		return ( LPASS_ERR_ARGS_INVALID );
	t_lpass_error	err = _handle_command( argv[ 1 ], args );
	if ( err != LPASS_OK )
		return ( err );
	if ( _needs_arg( args->cmd ) ) {
		if ( argc != 3 )
			return ( LPASS_ERR_ARGS_MISSING );
		err = _add_arg_to_cmd( args, argv[ 2 ] );
	}
	return ( err );
}

static char		*str_to_lower( char *str ) {
	size_t	str_len = strlen( str );
	char	*new = malloc( sizeof( char ) * ( str_len + 1 ) );
	if ( !new )
		return ( NULL );
	size_t	i = 0;
	while ( i < str_len ) {
		new[ i ] = tolower( str[ i ] );
		i++;
	}
	new[ i ] = '\0';
	return ( new );
}

static t_lpass_error	_handle_command( char *arg, t_args *args ) {
	if ( strlen( arg ) == 0 )
		return ( LPASS_ERR_ARGS_INVALID );
	char *lower_arg = str_to_lower( arg );
	if ( !lower_arg )
		return ( LPASS_ERR_MEMORY );
	if ( strcmp( lower_arg, "init" ) == 0 )
		args->cmd = LPASS_CMD_INIT;
	else if ( strcmp( lower_arg, "add" ) == 0 )
		args->cmd = LPASS_CMD_ADD;
	else if ( strcmp( lower_arg, "list" ) == 0 )
		args->cmd = LPASS_CMD_LIST;
	else if ( strcmp( lower_arg, "copy" ) == 0 )
		args->cmd = LPASS_CMD_COPY;
	else if ( strcmp( lower_arg, "delete" ) == 0 )
		args->cmd = LPASS_CMD_DEL;
	else if ( strcmp( lower_arg, "get" ) == 0 )
		args->cmd = LPASS_CMD_GET;
	else {
		args->cmd = LPASS_CMD_UNKNOWN;
		free( lower_arg );
		return ( LPASS_ERR_ARGS_INVALID );
	}
	free( lower_arg );
	return ( LPASS_OK );
}

static t_lpass_error	_add_arg_to_cmd( t_args *args, char *arg ) {
	if ( strlen( arg ) == 0 )
		return ( LPASS_ERR_ARGS_MISSING );
	args->argument = strdup( arg );
	if ( !args->argument )
		return ( LPASS_ERR_MEMORY );
	return ( LPASS_OK );
}

static int	_needs_arg( t_command cmd ) {
	return ( cmd == LPASS_CMD_COPY || cmd == LPASS_CMD_DEL || cmd == LPASS_CMD_GET );
}
