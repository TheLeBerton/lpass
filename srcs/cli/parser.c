#include "structures.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_cmd_policy {
	char		*str;
	t_command	cmd;
	int			needs_arg;
}	t_cmd_policy;

t_cmd_policy policies[] = {
	{ "init", LPASS_CMD_INIT, 0 },
	{ "add", LPASS_CMD_ADD, 0 },
	{ "list", LPASS_CMD_LIST, 0 },
	{ "gen", LPASS_CMD_GEN, 0 },
	{ "get", LPASS_CMD_GET, 1 },
	{ "copy", LPASS_CMD_COPY, 1 },
	{ "delete", LPASS_CMD_DEL, 1 }
};

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
	size_t	policies_size = sizeof( policies ) / sizeof( t_cmd_policy );
	args->cmd = LPASS_CMD_UNKNOWN;
	for ( size_t i = 0; i < policies_size; i++ ) {
		if (  strcmp( lower_arg, policies[ i ].str ) == 0 ) {
			args->cmd = policies[ i ].cmd;
			break ;
		}
	}
	free( lower_arg );
	if ( args->cmd == LPASS_CMD_UNKNOWN )
		return ( LPASS_ERR_ARGS_INVALID );
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
	size_t	policies_size = sizeof( policies ) / sizeof( t_cmd_policy );
	for ( size_t i = 0; i < policies_size; i++ ) {
		if ( policies[ i ].cmd == cmd )
			return ( policies[ i ].needs_arg );
	}
	return ( -1 );
}
