#ifndef CRYPTO_H
# define CRYPTO_H

# include "structures.h"
# include <stdint.h>

/**
 * @brief Derives a 32-byte encryption key from password and salt using Argon2id.
 * @return LPASS_OK on success, LPASS_ERR_MEMORY if Argon2id fails.
 */
t_lpass_error	derive_key( const char *password, const uint8_t *salt, uint8_t *key ) ;

/**
 * @brief Fills salt with size cryptographically random bytes (libsodium).
 * Call once at vault creation.
 */
void			generate_salt( uint8_t *salt, size_t size ) ;

/**
 * @brief Fills nonce with size cryptographically random bytes (libsodium).
 * Must be called on every vault_save to ensure nonce uniqueness.
 */
void			generate_nonce( uint8_t *nonce, size_t size ) ;

#endif
