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

TestSuite( entry_get, .init = setup, .fini = teardown );

Test( entry_get, null_vault_returns_error ) {
	t_vault	*vault = NULL;
	t_lpass_error	err;
	t_entry	*entry = entry_get( vault, "github", &err );
	cr_assert( err == LPASS_ERR_NULL );
	cr_assert_null( entry );
}

Test( entry_get, null_label ) {
	t_lpass_error	err;
	t_entry	*entry = entry_get( &vault, NULL, &err );
	cr_assert( err == LPASS_ERR_NULL );
	cr_assert_null( entry );
}

Test( entry_get, return_entry_on_success ) {
	t_lpass_error	err;
	t_entry	*entry = entry_get( &vault, "github", &err );
	cr_assert( err == LPASS_OK );
	cr_assert_not_null( entry );
}

Test( entry_get, not_found_returns_error ) {
	t_lpass_error	err;
	t_entry	*entry = entry_get( &vault, "nonexistent", &err );
	cr_assert( err == LPASS_ERR_NOT_FOUND );
	cr_assert_null( entry );
}

Test( entry_get, search_is_case_insensitive ) {
	t_lpass_error	err;
	t_entry	*entry = entry_get( &vault, "GiThuB", &err );
	cr_assert( err == LPASS_OK );
	cr_assert_not_null( entry );
}

Test( entry_get, returns_correct_entry_among_multiple ) {
	t_lpass_error err;
	t_entry_params	params1 = { "google", "google.com", "ftleo", "123", "blabla" };
	t_entry_params	params2 = { "reddit", "reddit.com", "ftleo", "123", "blabla" };
	entry_create( &vault , &params1, &err );
	entry_create( &vault , &params2, &err );
	t_entry	*entry = entry_get( &vault, "google", &err );
	cr_assert_str_eq( entry->label, "google" );
}
