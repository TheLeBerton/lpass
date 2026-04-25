#include "structures.h"
#include "entry.h"
#include "ui.h"
#include "vault.h"
#include "fs.h"
#include "crypto.h"


static t_lpass_error	_save_entry( t_vault *vault ) ;

t_lpass_error	cmd_delete( t_vault *vault, char *label ) {
	t_lpass_error	err;

	err = entry_delete( vault, label );
	if ( err != LPASS_OK )
		return ( err );
	err = _save_entry( vault );
	if ( err != LPASS_OK )
		return ( err );
	return ( LPASS_OK );
}

static t_lpass_error	_save_entry( t_vault *vault ) {
	t_lpass_error	err;
	char			password[ 256 ];
	char			path[ 512 ];
	uint8_t			key[ 32 ];

	err = prompt_master_password( password, sizeof( password ) );
	if ( err != LPASS_OK )
		return ( err );
	err = derive_key( password,vault->salt, key );
	if ( err != LPASS_OK )
		return ( err );
	err = get_vault_path( path, sizeof( path ) );
	if ( err != LPASS_OK )
		return ( err );
	err = vault_save( vault, path, key );
	if ( err != LPASS_OK )
		return ( err );
	return ( LPASS_OK );
}
