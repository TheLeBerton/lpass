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
	err = _write_file( vault, f );
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
	err = _read_file( vault, f );
	fclose( f );
	return ( err );
}
