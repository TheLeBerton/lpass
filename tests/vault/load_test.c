#include "entry.h"
#include "structures.h"
#include "vault.h"

#include <criterion/criterion.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static t_vault	*vault;
static char		path[ 64 ];

static void	setup( void ) {
	strcpy( path, "/tmp/lpass_test_XXXXXX" );
	int fd = mkstemp( path );
	close( fd );
	t_vault v = { 0 };
	vault_save( &v, path );
	vault = NULL;
}

static void	teardown( void ) {
	remove( "/home/leberton/.vault.test" );
	if ( vault ) {
		free( vault->entries );
		free( vault );
	}
}

TestSuite( vault_load, .init = setup, .fini = teardown );

Test( vault_load, path_is_NULL ) {
	t_lpass_error	err = vault_load( &vault, NULL );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( vault_load, path_is_empty ) {
	t_lpass_error	err = vault_load( &vault, "" );
	cr_assert( err == LPASS_WARN_EMPTY );
}

Test( vault_load, error_file ) {
	char			*path = "/root/.vault.test";
	t_lpass_error	err = vault_load( &vault, path );
	cr_assert( err == LPASS_ERR_FILE );
}

Test( vault_load, file_not_existing ) {
	char			*path = "/tmp/nonexistent_123.test";
	t_lpass_error	err = vault_load( &vault, path );
	cr_assert( err == LPASS_ERR_FILE );
}

Test( vault_load, happy_path ) {
	t_lpass_error	err = vault_load( &vault, path );
	cr_assert( err == LPASS_OK );
	cr_assert_not_null( vault );
}

Test( vault_load, round_trip ) {
	t_vault			src = { 0 };
	t_vault			*loaded = NULL;
	t_lpass_error	err;
	t_entry_params	p1 = { "github", "github.com", "ftleo", "123", "notes" };
	t_entry_params	p2 = { "google", "google.com", "ftleo", "123", "notes" };
	t_entry_params	p3 = { "reddit", "reddit.com", "ftleo", "123", "notes" };
	entry_create( &src, &p1, &err );
	entry_create( &src, &p2, &err );
	entry_create( &src, &p3, &err );
	vault_save( &src, path );
	err = vault_load( &loaded, path );
	cr_assert( err == LPASS_OK );
	cr_assert( loaded->entry_count == 3 );
	cr_assert_str_eq( loaded->entries[ 0 ].label, "github" );
	cr_assert_str_eq( loaded->entries[ 1 ].label, "google" );
	cr_assert_str_eq( loaded->entries[ 2 ].label, "reddit" );
	free( src.entries );
	free( loaded->entries );
	free( loaded );
}

