#include "entry.h"
#include "structures.h"
#include "entry_helpers.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

t_entry	*entry_create( t_vault *vault, t_entry_params *params, t_lpass_error *err ) {
	*err = LPASS_OK;
	if ( ( *err = _validate_params( vault, params ) ) != LPASS_OK )
		return ( NULL );
	if ( ( *err = _alloc_entry( vault ) ) != LPASS_OK )
		return ( NULL );
	t_entry	entry = _init_entry( params );
	vault->entries[ vault->entry_count ] = entry;
	vault->entry_count++;
	return &vault->entries[ vault->entry_count - 1 ];
}

t_entry	*entry_get( t_vault *vault, char *label, t_lpass_error *err ) {
	if ( !vault || !label ) {
		*err = LPASS_ERR_NULL;
		return ( NULL );
	}
	*err = LPASS_OK;
	for ( uint32_t i = 0; i < vault->entry_count; i++ ) {
		if ( strcasecmp( vault->entries[ i ].label, label ) == 0 )
			return ( &vault->entries[ i ] );
	}
	*err = LPASS_WARN_NOT_FOUND;
	return ( NULL );
}

t_entry	**entry_search( t_vault *vault, char *query, t_lpass_error *err ) {
	if ( !vault || !query ) {
		*err = LPASS_ERR_NULL;
		return ( NULL );
	}
	if ( strlen( query ) == 0 ) {
		*err = LPASS_WARN_NOT_FOUND;
		return ( NULL );
	}
	*err = LPASS_OK;
	t_entry **entries = malloc( sizeof( t_entry * ) );
	int		count = 0;
	if ( !entries ) {
		*err = LPASS_ERR_MEMORY;
		return ( NULL );
	}
	for ( uint32_t i = 0; i < vault->entry_count; i++ ) {
		if ( !_matches_queries( vault, query, i ) )
			continue;
		if ( ( *err = _alloc_entries( &entries, count ) ) != LPASS_OK )
			return ( NULL );
		entries[ count ] = &vault->entries[ i ];
		count++;
		entries[ count ] = NULL;
	}
	return ( entries );
}

t_lpass_error		entry_update( t_vault *vault, char *label, t_entry *new_data ) {
	if ( !vault || !label || !new_data )
		return LPASS_ERR_NULL;
	t_lpass_error err;
	t_entry *entry = entry_get( vault, label, &err);
	if ( !entry )
		return ( err );
	strlcpy( entry->label, new_data->label, sizeof( entry->label ) );
	strlcpy( entry->url, new_data->url, sizeof( entry->url ) );
	strlcpy( entry->username, new_data->username, sizeof( entry->username ) );
	strlcpy( entry->password, new_data->password, sizeof( entry->password ) );
	strlcpy( entry->notes, new_data->notes, sizeof( entry->notes ) );
	entry->updated_at = time( NULL );
	return ( LPASS_OK );
}

t_lpass_error		entry_delete( t_vault *vault, char *label ) {
	if ( !vault || !label )
		return LPASS_ERR_NULL;
	if ( vault->entry_count == 0 )
		return LPASS_WARN_EMPTY;
	uint32_t	entry_index;
	for ( entry_index = 0; entry_index < vault->entry_count; entry_index++ ) {
		if ( strcasecmp( vault->entries[ entry_index ].label, label ) == 0 )
			break ;
	}
	if ( entry_index == vault->entry_count )
		return ( LPASS_WARN_NOT_FOUND );
	for ( uint32_t i = entry_index; i < vault->entry_count; i++ ) {
		vault->entries[ i ] = vault->entries[ i + 1 ];
	}
	vault->entry_count--;
	t_entry	*tmp = realloc( vault->entries, ( vault->entry_count + 1 ) * sizeof( t_entry ) );
	if ( !tmp )
		return ( LPASS_ERR_MEMORY );
	vault->entries = tmp;
	return ( LPASS_OK );
}
