#include "structures.h"
#include "cli.h"
#include "fs.h"
#include "ui.h"
#include "vault.h"
#include "the_commands.h"

#include <stddef.h>
#include <stdlib.h>

typedef struct	s_cmd_policy {
	t_command		cmd;
	t_lpass_error	( *fn )( t_vault *, char * );
	int				needs_vault;
}	t_cmd_policy;


static t_cmd_policy policies[] = {
	{ LPASS_CMD_INIT, cmd_init, 0 },
	{ LPASS_CMD_GEN, cmd_gen, 0 },
	{ LPASS_CMD_ADD, cmd_add, 1 },
	{ LPASS_CMD_GET, cmd_get, 1 },
	{ LPASS_CMD_LIST, cmd_list, 1 },
	{ LPASS_CMD_COPY, cmd_copy, 1 },
	{ LPASS_CMD_DEL, cmd_delete, 1 },
};
size_t	policies_len = sizeof( policies ) / sizeof( t_cmd_policy );

t_lpass_error	_load_vault( t_vault **vault ) ;

t_lpass_error	handle_cmd( t_vault *vault, t_args args ) {
	t_lpass_error	err = LPASS_OK;
	int				loaded = 0;

	for ( size_t i = 0; i < policies_len; i++ ) {
		if ( policies[ i ].cmd == args.cmd ) {
			if ( policies[ i ].needs_vault ) {
				err = _load_vault( &vault );
				if ( err != LPASS_OK )
					break ;
				loaded = 1;
			}
			err = policies[ i ].fn( vault, args.argument );
			break ;
		}
	}
	if ( loaded ) {
		free( vault->entries );
		free( vault );
	}
	return ( err );
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
