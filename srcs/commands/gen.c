#include "structures.h"

#include <sodium.h>
#include <sodium/randombytes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

t_lpass_error	cmd_gen( t_vault *vault, char *label ) {
	(void)vault;
	int			n = ( label && atoi( label ) > 0 ) ? atoi( label ) : 20;
	if ( n < 4 )
		n = 4;
	const char	numbers[] = "0123456789";
	const char	lowercase[] = "abcdefghijklmnopqrstuvwxyz";
	const char	uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char	symbols[] = "!@#$^&*?";
	const char	charset[] = "0123456789"
							"abcdefghijklmnopqrstuvwxyz"
							"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							"!@#$^&*?";
	char	password[ n + 1 ];

	password[ 0 ] = numbers[ randombytes_uniform( 10 ) ];
	password[ 1 ] = lowercase[ randombytes_uniform( 26 ) ];
	password[ 2 ] = uppercase[ randombytes_uniform( 26 ) ];
	password[ 3 ] = symbols[ randombytes_uniform( 8 ) ];

	size_t	len = sizeof( charset ) - 1;
	for ( int i = 4; i < n; i++ ) 
		password[ i ] = charset[ randombytes_uniform( len ) ];
	for ( int i = n - 1; i > 0; i-- ) {
		int j = randombytes_uniform( i + 1 );
		char tmp = password[ i ];
		password[ i ] = password[ j ];
		password[ j ] = tmp;
	}
	password[ n ] = '\0';
	fprintf( stdout, "Your password is: %s\n", password );
	return ( LPASS_OK );
}
