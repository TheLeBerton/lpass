#include "structures.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <sys/stat.h>
#include <sodium.h>

t_lpass_error	derive_key( const char *password, const uint8_t *salt, uint8_t *key ) {
	if (crypto_pwhash(
			key, 32,
			password, strlen( password ),
			salt,
			crypto_pwhash_OPSLIMIT_INTERACTIVE,
			crypto_pwhash_MEMLIMIT_INTERACTIVE,
			crypto_pwhash_ALG_ARGON2ID13) != 0 )
		return ( LPASS_ERR_MEMORY );
	return ( LPASS_OK );
}

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
