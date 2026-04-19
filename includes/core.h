#ifndef CORE_H
# define CORE_H

# include "structures.h"

t_lpass_error	parse_args( int argc, char **argv, t_args *args ) ;
void			error_handler_args( t_lpass_error err ) ;


#endif
