#ifndef UI_H
# define UI_H

# include "structures.h"

t_lpass_error	prompt_password( char *out, size_t size ) ;
t_lpass_error	prompt_master_password( char *out, size_t size ) ;
t_lpass_error	prompt_add( t_entry_params	*params ) ;

#endif
