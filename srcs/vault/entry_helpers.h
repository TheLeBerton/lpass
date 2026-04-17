#ifndef ENTRY_HELPERS
#define ENTRY_HELPERS


#include "structures.h"


int				_is_empty( char *str );
t_lpass_error	_validate_params( t_vault *vault, t_entry_params *params );
t_lpass_error	_alloc_entry( t_vault *vault );
t_entry			_init_entry( t_entry_params *params );
int				_matches_queries( t_vault *vault, char *query, uint32_t i );
t_lpass_error	_alloc_entries( t_entry ***entries, int count );


#endif
