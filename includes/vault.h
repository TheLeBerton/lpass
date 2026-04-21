#ifndef VAULT_H
# define VAULT_H

# include "structures.h"

t_lpass_error	vault_save( t_vault *vault, char *path, uint8_t *key ) ;
t_lpass_error	vault_load( t_vault **vault, char *path, char *password ) ;

#endif
