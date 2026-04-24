#include "entry.h"
#include "structures.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>


/**
 * Returns 1 if `str` is an empty string, 0 otherwise.
 */
int	_is_empty( char *str ) {
	return ( strlen( str ) == 0 );
}

/**
 * Validates that `vault` and `params` are non-NULL and that required fields
 * (label, url, username, password) are non-empty.
 */
t_lpass_error	_validate_params( t_vault *vault, t_entry_params *params ) {
	if ( !vault || !params ) {
		return ( LPASS_ERR_NULL );
	}
	if ( _is_empty( params->label )
		|| _is_empty( params->url ) 
		|| _is_empty( params->username ) 
		|| _is_empty( params->password ) )
		return ( LPASS_WARN_EMPTY );
	t_lpass_error	err;
	if ( entry_get( vault, params->label, &err ) != NULL )
		return ( LPASS_ERR_ALREADY_EXISTS );
	return ( LPASS_OK );
}

/**
 * Grows `vault->entries` by one slot via realloc.
 */
t_lpass_error	_alloc_entry( t_vault *vault ) {
	t_entry	*tmp = realloc( vault->entries, ( vault->entry_count + 1 ) * sizeof( t_entry ) );
	if ( !tmp )
		return ( LPASS_ERR_MEMORY );
	vault->entries = tmp;
	return ( LPASS_OK );
}

/**
 * Initializes a new `t_entry` from `params`, generating a UUID and timestamps.
 */
t_entry	_init_entry( t_entry_params *params ) {
	t_entry	entry;
	generate_uuid( entry.id );
	strlcpy( entry.label, params->label, sizeof( entry.label ) );
	strlcpy( entry.url, params->url, sizeof( entry.url ) );
	strlcpy( entry.username, params->username, sizeof( entry.username ) );
	strlcpy( entry.password, params->password, sizeof( entry.password ) );
	strlcpy( entry.notes, params->notes, sizeof( entry.notes ) );
	entry.created_at = time(NULL );
	entry.updated_at = time(NULL );
	return ( entry );
}

/**
 * Returns 1 if entry at index `i` matches `query` in label, url or username.
 */
int	_matches_queries( t_vault *vault, char *query, uint32_t i ) {
	return (
		strcasestr( vault->entries[ i ].label, query ) != NULL ||
		strcasestr( vault->entries[ i ].url, query ) != NULL ||
		strcasestr( vault->entries[ i ].username, query ) != NULL
	);
}

/**
 * Grows the `entries` pointer array to fit `count + 1` entries plus a NULL terminator.
 */
t_lpass_error	_alloc_entries( t_entry ***entries, int count ) {
	t_entry	**tmp = realloc( *entries, ( count + 2 ) * sizeof( t_entry * ) );
	// TODO: FREE entries
	if ( !tmp )
		return ( LPASS_ERR_MEMORY );
	*entries = tmp;
	return ( LPASS_OK );
}
