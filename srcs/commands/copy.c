#include "structures.h"
#include "entry.h"
#include <stdio.h>


static t_lpass_error	_copy_to_clipboard( char *str ) ;

t_lpass_error	cmd_copy( t_vault *vault, char *label ) {
	t_entry			*entry;
	t_lpass_error	err;

	entry = entry_get( vault, label, &err );
	if ( err != LPASS_OK )
		return ( err );
	err = _copy_to_clipboard( entry->password );
	if ( err != LPASS_OK )
		return ( err );
	return ( LPASS_OK );
}

static t_lpass_error	_copy_to_clipboard( char *str ) {
	FILE	*pipe = popen( "xclip -selection clipboard", "w" );
	if ( !pipe )
		return ( LPASS_ERR_MEMORY );
	fputs( str, pipe );
	pclose( pipe );
	return ( LPASS_OK );
}
