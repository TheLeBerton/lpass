#include "structures.h"
#include "vault_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Saves a `vault` to `path` in raw bytes.
 */
t_lpass_error	vault_save( t_vault *vault, char *path ) {
	t_lpass_error	err = _validate_save_params( vault, path );
	if ( err != LPASS_OK )
		return ( err );
	FILE *f = fopen( path, "wb" );
	if ( !f )
		return ( LPASS_ERR_FILE );
	err = _serialize_vault( vault, f );
	fclose( f );
	return ( err );
}

/**
 * Loads a `vault` from `path`.
 */
t_lpass_error	vault_load( t_vault **vault, char *path ) {
	t_lpass_error	err = _validate_load_params( vault, path );
	if ( err != LPASS_OK )
		return ( err );
	FILE *f = fopen( path, "rb" );
	if ( !f )
		return ( LPASS_ERR_FILE );
	t_vault	*v = malloc( sizeof( t_vault ) );
	if ( !v ) {
		fclose( f );
		return ( LPASS_ERR_MEMORY );
	}
	err = _deserialize_vault( v, f );
	fclose( f );
	if ( err != LPASS_OK ) {
		free( v );
		return ( err );
	}
	*vault = v;
	return ( err );
}
