#ifndef CORE_H
# define CORE_H

# include "structures.h"

t_lpass_error	parse_args( int argc, char **argv, t_args *args ) ;
void			error_handler_args( t_lpass_error err ) ;
void			error_handler_init( t_lpass_error err ) ;

t_lpass_error	derive_key( const char *password, const uint8_t *salt, uint8_t *key ) ;

t_lpass_error	prompt_password( char *out, size_t size ) ;


#endif
