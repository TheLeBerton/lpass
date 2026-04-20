#include "structures.h"
#include "vault.h"
#include "core.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <sodium.h>
#include <sys/stat.h>

static t_lpass_error	_init_lpass( char *path, size_t size, t_vault *vault );

t_lpass_error	cmd_init( t_vault *vault ) {
	t_lpass_error err;
	uint8_t	key[ 32 ];
	randombytes_buf( vault->salt, sizeof( vault->salt ) );
	char	path[ 512 ];
	err = _init_lpass( path, sizeof( path ), vault );
	if ( err != LPASS_OK )
		return ( err );
	char password[ 256 ];
	err = prompt_password( password, sizeof( password ) );
	if ( err != LPASS_OK )
		return ( err );
	err = derive_key( password, vault->salt, key );
	if ( err != LPASS_OK )
		return ( err );
	return ( LPASS_OK );
}


static t_lpass_error	_init_lpass( char *path, size_t size, t_vault *vault ) {
	t_lpass_error err;
	char dir[ 512 ];
	if ( getenv( "HOME" ) == NULL )
		return ( LPASS_ERR_NULL );
	snprintf( dir, sizeof( dir ), "%s/.lpass", getenv( "HOME" ) );
	mkdir( dir, 0700 );
	snprintf( path, size, "%s/.lpass/vault", getenv( "HOME" ) );
	struct stat	st;
	if ( stat( path, &st ) == 0 ) {
		return ( LPASS_ERR_ALREADY_EXISTS );
	}
	err = vault_save( vault, path );
	if ( err != LPASS_OK )
		return ( err );
	return ( LPASS_OK );
}
