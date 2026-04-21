#include "structures.h"
#include "vault.h"
#include "crypto.h"

#include <criterion/criterion.h>
#include <sodium.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static t_vault		*vault;
static char			path[ 64 ];
static uint8_t		test_key[ 32 ];
static char			test_password[] = "testpassword123";

static void	setup( void ) {
	if ( sodium_init() < 0 )
		return ;
	strcpy( path, "/tmp/lpass_test_XXXXXX" );
	int fd = mkstemp( path );
	close( fd );
	t_vault v = { 0 };
	generate_salt( v.salt, sizeof( v.salt ) );
	generate_nonce( v.nonce, sizeof( v.nonce ) );
	derive_key( test_password, v.salt, test_key );
	vault_save( &v, path, test_key );
	vault = NULL;
}

static void	teardown( void ) {
	remove( path );
	if ( vault ) {
		free( vault->entries );
		free( vault );
	}
}

TestSuite( vault_load, .init = setup, .fini = teardown );

Test( vault_load, path_is_NULL ) {
	t_lpass_error	err = vault_load( &vault, NULL, test_password );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( vault_load, path_is_empty ) {
	t_lpass_error	err = vault_load( &vault, "", test_password );
	cr_assert( err == LPASS_WARN_EMPTY );
}

Test( vault_load, error_file ) {
	char			*path = "/root/.vault.test";
	t_lpass_error	err = vault_load( &vault, path, test_password );
	cr_assert( err == LPASS_ERR_FILE );
}

Test( vault_load, file_not_existing ) {
	char			*path = "/tmp/nonexistent_123.test";
	t_lpass_error	err = vault_load( &vault, path, test_password );
	cr_assert( err == LPASS_ERR_FILE );
}

Test( vault_load, happy_path ) {
	t_lpass_error	err = vault_load( &vault, path, test_password );
	cr_assert( err == LPASS_OK );
	cr_assert_not_null( vault );
}

Test( vault_load, round_trip ) {
	t_vault			src = { 0 };
	t_vault			*loaded = NULL;
	t_lpass_error	err;
	uint8_t			key[ 32 ];

	generate_salt( src.salt, sizeof( src.salt ) );
	generate_nonce( src.nonce, sizeof( src.nonce ) );
	derive_key( test_password, src.salt, key );
	vault_save( &src, path, key );
	err = vault_load( &loaded, path, test_password );
	cr_assert( err == LPASS_OK );
	cr_assert( loaded->entry_count == 0 );
	cr_assert_null( loaded->entries );
	free( loaded );
}
