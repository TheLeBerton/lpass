#ifndef THE_COMMANDS_H
# define THE_COMMANDS_H

# include "structures.h"

t_lpass_error	cmd_init( t_vault *vault ) ;
t_lpass_error	cmd_add( t_vault *vault ) ;
t_lpass_error	cmd_get( t_vault *vault, char *label ) ;
t_lpass_error	cmd_list( t_vault *vault ) ;
t_lpass_error	cmd_copy( t_vault *vault, char *label ) ;
t_lpass_error	cmd_delete( t_vault *vault, char *label ) ;

#endif
