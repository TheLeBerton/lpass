#include "structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

t_lpass_error	init_lpass_dir( char *path, size_t size ) {
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
	return ( LPASS_OK );
}
