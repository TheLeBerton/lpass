#include "structures.h"

#include <stdint.h>
#include <string.h>
#include <sodium.h>

t_lpass_error	derive_key( const char *password, const uint8_t *salt, uint8_t *key ) {
	if (crypto_pwhash(
			key, 32,
			password, strlen( password ),
			salt,
			crypto_pwhash_OPSLIMIT_INTERACTIVE,
			crypto_pwhash_MEMLIMIT_INTERACTIVE,
			crypto_pwhash_ALG_ARGON2ID13) != 0 )
		return ( LPASS_ERR_MEMORY );
	return ( LPASS_OK );
}

