#include "structures.h"
#include "entry.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <criterion/parameterized.h>

static t_vault	vault;

static t_vault	fresh_vault( void ) {
	t_vault	vault = { 0 };
	return ( vault );
}

static void	setup( void ) {
	vault = fresh_vault();
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "blabla" };
	t_lpass_error	err;
	entry_create( &vault, &params, &err );
}

static void	teardown( void ) {
	free( vault.entries );
}

TestSuite( entry_delete, .init = setup, .fini = teardown );

Test( entry_delete, null_vault_returns_error ) {
	t_lpass_error	err = entry_delete( NULL, "github" );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( entry_delete, null_label_returns_error ) {
	t_lpass_error	err = entry_delete( &vault, NULL );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( entry_delete, empty_vault_returns_error_empty ) {
	t_vault	vault = { 0 };
	t_lpass_error	err = entry_delete( &vault, "github" );
	cr_assert( err == LPASS_ERR_EMPTY );
}

Test( entry_delete, entry_gets_deleted ) {
	t_lpass_error	err = entry_delete( &vault, "github" );
	cr_assert( err == LPASS_OK );
	cr_assert( vault.entry_count == 0 );
}

Test( entry_delete, correct_entry_gets_deleted ) {
	t_entry_params	params = { "google", "google.com", "ftleo", "123", "blabla" };
	t_lpass_error	err;
	entry_create( &vault, &params, &err );
	err = entry_delete( &vault, "google" );
	cr_assert( err == LPASS_OK );
	cr_assert( vault.entry_count == 1 );
	cr_assert_str_eq( vault.entries[ 0 ].label, "github" );
}
