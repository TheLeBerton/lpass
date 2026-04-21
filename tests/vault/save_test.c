#include "structures.h"
#include "vault.h"
#include "crypto.h"

#include <criterion/criterion.h>
#include <sodium.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static t_vault		vault;
static char			path[ 64 ];
static uint8_t		test_key[ 32 ];
static char			test_password[] = "testpassword123";

static t_vault	fresh_vault( void ) {
	t_vault	v = { 0 };
	generate_salt( v.salt, sizeof( v.salt ) );
	generate_nonce( v.nonce, sizeof( v.nonce ) );
	return ( v );
}

static void	setup( void ) {
	if ( sodium_init() < 0 )
		return ;
	strcpy( path, "/tmp/lpass_test_XXXXXX" );
	int fd = mkstemp( path );
	close( fd );
	vault = fresh_vault();
	derive_key( test_password, vault.salt, test_key );
}

static void	teardown( void ) {
	remove( path );
}

TestSuite( vault_save, .init = setup, .fini = teardown );

Test( vault_save, vault_is_NULL ) {
	t_lpass_error	err = vault_save( NULL, path, test_key );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( vault_save, path_is_NULL ) {
	t_lpass_error	err = vault_save( &vault, NULL, test_key );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( vault_save, path_is_empty ) {
	t_lpass_error	err = vault_save( &vault, "", test_key );
	cr_assert( err == LPASS_WARN_EMPTY );
}

Test( vault_save, error_file ) {
	char			*path = "/root/.vault.test";
	t_lpass_error	err = vault_save( &vault, path, test_key );
	cr_assert( err == LPASS_ERR_FILE );
}

Test( vault_save, happy_path ) {
	t_lpass_error	err = vault_save( &vault, path, test_key );
	cr_assert( err == LPASS_OK );
}
