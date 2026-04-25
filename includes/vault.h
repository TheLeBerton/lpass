#ifndef VAULT_H
# define VAULT_H

# include "structures.h"

/**
 * @brief Encrypts and writes the vault to disk using XChaCha20-Poly1305.
 * File layout: [ salt:32 ][ nonce:24 ][ ciphertext_len:8 ][ ciphertext ].
 * @return LPASS_OK on success, LPASS_ERR_FILE on write error.
 */
t_lpass_error	vault_save( t_vault *vault, char *path, uint8_t *key ) ;

/**
 * @brief Reads and decrypts a vault from disk.
 * Re-derives the key with Argon2id using the stored salt and password.
 * Allocates *vault on success — caller must free vault->entries and vault.
 * @return LPASS_OK on success, LPASS_ERR_FILE if read fails or password is wrong.
 */
t_lpass_error	vault_load( t_vault **vault, char *path, char *password ) ;

#endif
