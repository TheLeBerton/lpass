#include "structures.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>

static t_lpass_error	_prompt_master_password( char *prompt, char *out, size_t size );

t_lpass_error	prompt_password( char *out, size_t size ) {
	char	confirm[ 256 ];
	if ( _prompt_master_password( "Master password: ", out,  size ) != LPASS_OK )
		return ( LPASS_ERR_NULL );
	if ( _prompt_master_password( "Confirm master password: ", confirm, sizeof( confirm ) ) != LPASS_OK )
		return ( LPASS_ERR_NULL );
	if ( strcmp( out, confirm ) != 0 )
		return ( LPASS_ERR_ARGS_INVALID );
	return ( LPASS_OK );
}

t_lpass_error	prompt_master_password( char *out, size_t size ) {
	if ( _prompt_master_password( "Master password: ", out,  size ) != LPASS_OK )
		return ( LPASS_ERR_NULL );
	return ( LPASS_OK );
}

static t_lpass_error	prompt_param( char *prompt, char *out, size_t size );

t_lpass_error	prompt_add( t_entry_params	*params ) {
	t_lpass_error	err;

	err = prompt_param( "Label: ", params->label, sizeof( params->label ) );
	if ( err != LPASS_OK )
		return ( err );
	err = prompt_param( "URL: ", params->url, sizeof( params->url ) );
	if ( err != LPASS_OK )
		return ( err );
	err = prompt_param( "Username: ", params->username, sizeof( params->username ) );
	if ( err != LPASS_OK )
		return ( err );
	if ( _prompt_master_password( "Password: ", params->password,  sizeof( params->password ) ) != LPASS_OK )
		return ( LPASS_ERR_NULL );
	err = prompt_param( "Notes ( can be empty ): ", params->notes, sizeof( params->notes ) );
	if ( err != LPASS_OK )
		return ( err );
	return ( LPASS_OK );
}

static t_lpass_error	prompt_param( char *prompt, char *out, size_t size ) {
	fprintf( stdout, "%s", prompt );
	if ( fgets( out, size, stdin ) == NULL )
		return ( LPASS_ERR_NULL );
	size_t	len = strlen( out );
	if ( len > 0 && out[ len - 1 ] == '\n' )
		out[ len - 1 ] = '\0';
	return ( LPASS_OK );
}

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


