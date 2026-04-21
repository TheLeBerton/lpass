#include "structures.h"

#include <sodium/crypto_aead_xchacha20poly1305.h>
#include <sodium/crypto_pwhash.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <threads.h>
#include <time.h>


t_lpass_error	_validate_save_params( t_vault *vault, char *path ) {
	if ( !vault || !path )
		return ( LPASS_ERR_NULL );
	if ( strlen( path ) == 0 )
		return ( LPASS_WARN_EMPTY );
	return ( LPASS_OK );
}

t_lpass_error	_validate_load_params( t_vault **vault, char *path ) {
	if ( !vault || !path )
		return ( LPASS_ERR_NULL );
	if ( strlen( path ) == 0 )
		return ( LPASS_WARN_EMPTY );
	return ( LPASS_OK );
}

t_lpass_error	_serialize_entries( t_vault *vault, uint8_t *key, unsigned char **cipher, size_t *cipher_len ) {
	unsigned char	*plaintext = ( unsigned char *)&vault->entry_count;
	size_t			plaintext_len = sizeof( uint32_t );
	size_t			ciphertext_len = plaintext_len + crypto_aead_xchacha20poly1305_ietf_ABYTES;
	unsigned char	*ciphertext = malloc( ciphertext_len );
	if ( !ciphertext )
		return ( LPASS_ERR_MEMORY );
	unsigned long long	actual_len;
	crypto_aead_xchacha20poly1305_ietf_encrypt(
		ciphertext, &actual_len,
		plaintext, plaintext_len, 
		NULL, 0, 
		NULL, 
		vault->nonce, 
		key
	);
	*cipher = ciphertext;
	*cipher_len = ciphertext_len;
	return ( LPASS_OK );
}

t_lpass_error	_serialize_vault( t_vault *vault, FILE *f, uint8_t *key ) {
	size_t			bytes_written;
	t_lpass_error	err;
	unsigned char	*ciphertext;
	size_t			ciphertext_len;

	bytes_written = fwrite( &vault->salt, sizeof( vault->salt ), 1, f );
	if ( bytes_written < 1 )
		return ( LPASS_ERR_FILE );
	bytes_written = fwrite( &vault->nonce, sizeof( vault->nonce ), 1, f );
	if ( bytes_written < 1 )
		return ( LPASS_ERR_FILE );
	err = _serialize_entries( vault, key, &ciphertext, &ciphertext_len );
	if ( err != LPASS_OK )
		return ( err );
	bytes_written = fwrite( &ciphertext_len, sizeof( size_t ), 1, f );
	if ( bytes_written < 1 )
		return ( LPASS_ERR_FILE );
	bytes_written = fwrite( ciphertext, ciphertext_len, 1, f );
	if ( bytes_written < 1 ) {
		free( ciphertext );
		return ( LPASS_ERR_FILE );
	}
	free( ciphertext );
	return ( LPASS_OK );
}

static t_lpass_error	_read_vault_header( t_vault *v, FILE *f, unsigned char **cipher, unsigned long long *cipher_len );
static t_lpass_error	_decrypt_entries( t_vault *v, unsigned char *cipher, unsigned long long cipher_len,
								char *password, unsigned char **plain, unsigned long long *plain_len );
static t_lpass_error	_parse_entries( t_vault *v, unsigned char *plain );

t_lpass_error	_deserialize_vault( t_vault *v, FILE *f, char *password ) {
	unsigned char		*cipher = NULL;
	unsigned char		*plain = NULL;
	unsigned long long	cipher_len;
	unsigned long long	plain_len;
	t_lpass_error		err;

	err = _read_vault_header( v, f, &cipher, &cipher_len );
	if ( err != LPASS_OK ) {
		if ( cipher )
			free( cipher );
		return ( err );
	}
	err = _decrypt_entries( v, cipher, cipher_len, password, &plain, &plain_len);
	if ( err == LPASS_OK )
		err = _parse_entries( v, plain );
	if ( cipher )
		free( cipher );
	if ( plain )
		free( plain );
	return ( err );
}

static t_lpass_error	_read_vault_header( t_vault *v, FILE *f, unsigned char **cipher, unsigned long long *cipher_len ) {
	if ( fread( &v->salt, 1, sizeof( v->salt ), f ) == 0 )
		return ( LPASS_ERR_FILE );
	if ( fread( &v->nonce, 1, sizeof( v->nonce ), f ) == 0 )
		return ( LPASS_ERR_FILE );
	if ( fread( cipher_len, sizeof( unsigned long long ), 1, f ) == 0 )
		return ( LPASS_ERR_FILE );
	*cipher = malloc( *cipher_len );
	if ( !*cipher )
		return ( LPASS_ERR_MEMORY );
	if ( fread( *cipher, *cipher_len, 1, f ) == 0 )
		return ( LPASS_ERR_FILE );
	return ( LPASS_OK );
}

static t_lpass_error	_decrypt_entries( t_vault *v, unsigned char *cipher, unsigned long long cipher_len,
								char *password, unsigned char **plain, unsigned long long *plain_len ) {
	uint8_t				r_key[ 32 ];

	if ( crypto_pwhash(
		r_key, 32,
		password, strlen( password ),
		v->salt,
		crypto_pwhash_OPSLIMIT_INTERACTIVE,
		crypto_pwhash_MEMLIMIT_INTERACTIVE,
		crypto_pwhash_ALG_ARGON2ID13 ) != 0 )
		return ( LPASS_ERR_MEMORY );
	*plain = malloc( cipher_len - crypto_aead_xchacha20poly1305_ietf_ABYTES );
	if ( !*plain )
		return ( LPASS_ERR_MEMORY );
	int	ret = crypto_aead_xchacha20poly1305_ietf_decrypt(
		*plain, plain_len, 
		NULL, 
		cipher, cipher_len, 
		NULL, 0,
		v->nonce,
		r_key
	);
	if ( ret != 0 )
		return ( LPASS_ERR_FILE );
	return ( LPASS_OK );
}

static t_lpass_error	_parse_entries( t_vault *v, unsigned char *plain ) {
	uint32_t	count;
	memcpy( &count, plain, sizeof( uint32_t ) );
	v->entry_count = count;
	v->entries = NULL;
	return ( LPASS_OK );
}
