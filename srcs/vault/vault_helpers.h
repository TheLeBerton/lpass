#ifndef VAULT_HELPERS_H
# define VAULT_HELPERS_H

#include "structures.h"

#include <stdio.h>

t_lpass_error	_validate_save_params( t_vault *vault, char *path ) ;
t_lpass_error	_validate_load_params( t_vault **vault, char *path ) ;
t_lpass_error	_serialize_vault( t_vault *vault, FILE *f, uint8_t *key ) ;
t_lpass_error	_deserialize_vault( t_vault *vault, FILE *f, char *password ) ;

#endif
