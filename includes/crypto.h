#ifndef CRYPTO_H
# define CRYPTO_H

# include "structures.h"
# include <stdint.h>

t_lpass_error	derive_key( const char *password, const uint8_t *salt, uint8_t *key ) ;
void			generate_salt( uint8_t *salt, size_t size ) ;

#endif
