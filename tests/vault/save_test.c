#include "structures.h"
#include "vault.h"

#include <criterion/criterion.h>
#include <unistd.h>
#include <stdio.h>

static t_vault	vault;
static char		path[ 64 ];

static t_vault	fresh_vault( void ) {
	t_vault	vault = { 0 };
	return ( vault );
}

static void	setup( void ) {
	strcpy( path, "/tmp/lpass_test_XXXXXX" );
	int fd = mkstemp( path );
	close( fd );
	vault = fresh_vault();
}

static void	teardown( void ) {
	remove( "/home/leberton/.vault.test" );
}

TestSuite( vault_save, .init = setup, .fini = teardown );

Test( vault_save, vault_is_NULL ) {
	t_lpass_error	err = vault_save( NULL, path );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( vault_save, path_is_NULL ) {
	t_lpass_error	err = vault_save( &vault, NULL );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( vault_save, path_is_empty ) {
	t_lpass_error	err = vault_save( &vault, "" );
	cr_assert( err == LPASS_WARN_EMPTY );
}

Test( vault_save, error_file ) {
	char			*path = "/root/.vault.test";
	t_lpass_error	err = vault_save( &vault, path );
	cr_assert( err == LPASS_ERR_FILE );
}

Test( vault_save, happy_path ) {
	t_lpass_error	err = vault_save( &vault, path );
	cr_assert( err == LPASS_OK );
}

