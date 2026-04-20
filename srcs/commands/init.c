#include "structures.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

static t_lpass_error	_prompt_master_password( char *prompt, char *out, size_t size ) {
	struct termios	old;
	struct termios	hidden;

	tcgetattr( STDIN_FILENO, &old );
	hidden = old;
	hidden.c_lflag &= ~ECHO;
	tcsetattr( STDIN_FILENO, TCSANOW, &hidden );
	printf( "%s", prompt );
	fflush( stdout );
	if ( fgets( out, size, stdin ) == NULL ) {
		tcsetattr( STDIN_FILENO, TCSANOW, &old );
		return ( LPASS_ERR_NULL );
	}
	tcsetattr( STDIN_FILENO, TCSANOW, &old );
	printf( "\n" );
	size_t	len = strlen( out );
	if ( len > 0 && out[ len - 1 ] == '\n' )
		out[ len - 1 ] = '\0';
	return ( LPASS_OK );
}

t_lpass_error	cmd_init() {
	char	password[ 256 ];
	char	confirm[ 256 ];

	if ( _prompt_master_password( "Master password: ", password, sizeof( password ) ) != LPASS_OK )
		return ( LPASS_ERR_NULL );
	if ( _prompt_master_password( "Confirm master password: ", confirm, sizeof( password ) ) != LPASS_OK )
		return ( LPASS_ERR_NULL );
	if ( strcmp( password, confirm ) != 0 ) {
		fprintf( stderr, "Passwords do not match.\n" );
		return ( LPASS_ERR_ARGS_INVALID );
	}
	return ( LPASS_OK );
}
