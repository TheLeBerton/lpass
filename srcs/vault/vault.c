#include "structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_lpass_error	vault_save( t_vault *vault, char *path ) {
	if ( !vault || !path )
		return ( LPASS_ERR_NULL );
	if ( strlen( path ) == 0 )
		return ( LPASS_WARN_EMPTY );
	FILE *f = fopen( path, "wb" );
	if ( !f )
		return ( LPASS_ERR_FILE );
	size_t	bytes_written;
	bytes_written = fwrite( &vault->entry_count, sizeof( uint32_t ), 1, f );
	if (bytes_written < 1 ) {
		fclose( f );
		return ( LPASS_ERR_FILE );
	}
	if ( vault->entry_count > 0 ) {
		bytes_written = fwrite( vault->entries, sizeof( t_entry ), vault->entry_count, f );
		if (bytes_written < vault->entry_count ) {
			fclose( f );
			return ( LPASS_ERR_FILE );
		}
	}
	if ( fclose( f ) == EOF )
		return ( LPASS_ERR_FILE );
	return ( LPASS_OK );
}

t_lpass_error	vault_load( t_vault **vault, char *path ) {
	if ( !vault || !path )
		return ( LPASS_ERR_NULL );
	if ( strlen( path ) == 0 )
		return ( LPASS_WARN_EMPTY );
	t_vault	*v;
	v = malloc( sizeof( t_vault ) );
	if ( !v )
		return ( LPASS_ERR_MEMORY );
	FILE *f = fopen( path, "rb" );
	if ( !f ) {
		free( v );
		return ( LPASS_ERR_FILE );
	}
	size_t	bytes_read;
	bytes_read = fread( &v->entry_count, sizeof( uint32_t ), 1, f );
	if ( bytes_read == 0 ) {
		free( v );
		fclose( f );
		return ( LPASS_ERR_FILE );
	}
	if ( v->entry_count == 0 ) {
		fclose( f );
		v->entries = NULL;
		*vault = v;
		return ( LPASS_OK );
	}
	v->entries = malloc( sizeof( t_entry ) * v->entry_count );
	if ( !v->entries ) {
		free( v );
		fclose( f );
		return ( LPASS_ERR_MEMORY );
	}
	bytes_read = fread( v->entries, sizeof( t_entry ), v->entry_count, f );
	if ( bytes_read != v->entry_count ) {
		free( v->entries );
		free( v );
		fclose( f );
		return ( LPASS_ERR_FILE );
	}
	*vault = v;
	fclose( f );
	return ( LPASS_OK );
}
