#ifndef CLI_H
# define CLI_H

# include "structures.h"

t_lpass_error	parse_args( int argc, char **argv, t_args *args ) ;
void			error_handler_args( t_lpass_error err ) ;
void			error_handler_init( t_lpass_error err ) ;
void			error_handler_copy( t_lpass_error err ) ;

#endif
