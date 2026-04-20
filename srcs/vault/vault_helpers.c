#include "structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


t_lpass_error	_validate_save_params( t_vault *vault, char *path ) {
	if ( !vault || !path )
		return ( LPASS_ERR_NULL );
	if ( strlen( path ) == 0 )
		return ( LPASS_WARN_EMPTY );
	return ( LPASS_OK );
}

t_lpass_error	_validate_load_params( t_vault **vault, char *path ) {
	if ( !vault || !path )
		return ( LPASS_ERR_NULL );
	if ( strlen( path ) == 0 )
		return ( LPASS_WARN_EMPTY );
	return ( LPASS_OK );
}

t_lpass_error	_serialize_vault( t_vault *vault, FILE *f ) {
	size_t	bytes_written;
	bytes_written = fwrite( &vault->entry_count, sizeof( uint32_t ), 1, f );
	if ( bytes_written < 1 )
		return ( LPASS_ERR_FILE );
	if ( vault->entry_count > 0 ) {
		bytes_written = fwrite( vault->entries, sizeof( t_entry ), vault->entry_count, f );
		if ( bytes_written < vault->entry_count )
			return ( LPASS_ERR_FILE );
	}
	return ( LPASS_OK );
}

t_lpass_error	_deserialize_vault( t_vault *v, FILE *f ) {
	if ( fread( &v->entry_count, sizeof( uint32_t ), 1, f ) == 0 )
		return ( LPASS_ERR_FILE );
	if ( v->entry_count == 0 ) {
		v->entries = NULL;
		return ( LPASS_OK );
	}
	v->entries = malloc( sizeof( t_entry ) * v->entry_count );
	if ( !v->entries )
		return ( LPASS_ERR_MEMORY );
	if ( fread( v->entries, sizeof( t_entry ), v->entry_count, f ) != v->entry_count ) {
		free( v->entries );
		return ( LPASS_ERR_FILE );
	}
	return ( LPASS_OK );
}

