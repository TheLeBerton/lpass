#ifndef VAULT_HELPERS_H
# define VAULT_HELPERS_H

#include "structures.h"

#include <stdio.h>

t_lpass_error	_validate_save_params( t_vault *vault, char *path ) ;
t_lpass_error	_validate_load_params( t_vault **vault, char *path ) ;
t_lpass_error	_write_file( t_vault *vault, FILE *f ) ;
t_lpass_error	_read_file( t_vault **vault, FILE *f ) ;

#endif
