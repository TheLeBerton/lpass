#include "crypto.h"
#include "structures.h"
#include "ui.h"
#include "fs.h"
#include "entry.h"
#include "vault.h"
#include <stdint.h>

static t_lpass_error	_save_entry( t_vault *vault ) ;

t_lpass_error	cmd_add( t_vault *vault, char *label ) {
	(void)label;
	t_entry_params	params;
	t_lpass_error	err;

	err = prompt_add( &params );
	if ( err != LPASS_OK )
		return ( err );
	entry_create( vault, &params, &err );
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
