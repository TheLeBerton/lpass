#include "structures.h"
#include "crypto.h"
#include "ui.h"
#include "fs.h"
#include "vault.h"


t_lpass_error	cmd_init( t_vault *vault, char *label ) {
	(void)label;
	t_lpass_error	err;
	uint8_t			key[ 32 ];
	char			path[ 512 ];
	char 			password[ 256 ];

	err = init_lpass_dir( path, sizeof( path ) );
	if ( err != LPASS_OK )
		return ( err );
	err = prompt_password( password, sizeof( password ) );
	if ( err != LPASS_OK )
		return ( err );
	generate_salt( vault->salt, sizeof( vault->salt ) );
	generate_nonce( vault->nonce, sizeof( vault->nonce ) );
	err = derive_key( password, vault->salt, key );
	if ( err != LPASS_OK )
		return ( err );
	err = vault_save( vault, path, key );
	if ( err != LPASS_OK )
		return ( err );
	return ( LPASS_OK );
}


