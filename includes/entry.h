#ifndef ENTRY_H
# define ENTRY_H

#include "structures.h"


t_entry			*entry_create( t_vault *vault, t_entry_params *params, t_lpass_error *err ) ;
t_entry			*entry_get( t_vault *vault, char *label, t_lpass_error *err ) ;
t_entry			**entry_search( t_vault *vault, char *query, t_lpass_error *err ) ;
t_lpass_error	entry_update( t_vault *vault, char *label, t_entry *new_data ) ;
t_lpass_error	entry_delete( t_vault *vault, char *label ) ;


#endif
