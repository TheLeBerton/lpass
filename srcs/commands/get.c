#include "structures.h"
#include "entry.h"
#include <stdio.h>


t_lpass_error	cmd_get( t_vault *vault, char *label ) {
	t_entry			*entry;
	t_lpass_error	err;

	entry = entry_get( vault, label, &err );
	if ( err != LPASS_OK )
		return ( err );
	printf( "Label: %s\n", entry->label );
	printf( "URL: %s\n", entry->url );
	printf( "Username: %s\n", entry->username );
	printf( "Notes: %s\n", entry->notes );
	return ( LPASS_OK );
}
