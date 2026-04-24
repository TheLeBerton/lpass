#include "structures.h"
#include "entry.h"

#include <stdio.h>

t_lpass_error	cmd_list( t_vault *vault ) {
	t_lpass_error	err;
	t_entry			*entry;

	for ( uint32_t i = 0; i < vault->entry_count; i++ ) {
		entry = entry_get( vault, vault->entries[ i ].label, &err );
		if ( err != LPASS_OK )
			return ( err );
		printf( "Label: %s\n", entry->label );
		printf( "URL: %s\n", entry->url );
		printf( "Username: %s\n\n", entry->username );
	}
	return ( LPASS_OK );
}

