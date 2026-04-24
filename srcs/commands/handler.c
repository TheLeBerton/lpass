#include "structures.h"
#include "cli.h"
#include "fs.h"
#include "ui.h"
#include "vault.h"
#include "the_commands.h"

t_lpass_error	_load_vault( t_vault **vault ) ;

t_lpass_error	handle_cmd( t_vault *vault, t_args args ) {
	t_lpass_error	err;

	if ( args.cmd == LPASS_CMD_INIT ) {
		err = cmd_init( vault );
		if ( err != LPASS_OK ) {
			error_handler_init( err );
			return ( err );
		}
		return ( LPASS_OK );
	}
	err = _load_vault( &vault );
	if ( err != LPASS_OK )
		return ( err );
	if ( args.cmd == LPASS_CMD_ADD ) {
		err = cmd_add( vault );
		if ( err != LPASS_OK ) {
			return ( err );
		}
	}
	else if ( args.cmd == LPASS_CMD_GET ) {
		err = cmd_get( vault, args.argument );
		if ( err != LPASS_OK ) {
			return ( err );
		}
	}
	return ( LPASS_OK );
}

t_lpass_error	_load_vault( t_vault **vault ) {
	t_lpass_error	err;
	char			path[ 512 ];
	char			password[ 256 ];

	err = get_vault_path( path, sizeof( path ) );
	if ( err != LPASS_OK )
		return ( err );
	err = prompt_master_password( password, sizeof( password ) );
	if ( err != LPASS_OK )
		return ( err );
	err = vault_load( vault, path, password );
	if ( err != LPASS_OK )
		return ( err );
	return ( LPASS_OK );
}
