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
	t_entry_params	params1 = { "google", "google.com", "ftleo", "123", "blabla" };
	t_entry_params	params2 = { "google", "google.com", "ccleo", "123", "blabla" };
	t_lpass_error	err;
	entry_create( &vault, &params, &err );
	entry_create( &vault, &params1, &err );
	entry_create( &vault, &params2, &err );
}

static void	teardown( void ) {
	free( vault.entries );
}

TestSuite( entry_search, .init = setup, .fini = teardown );


Test( entry_search, null_vault_returns_error ) {
	t_vault	*vault = NULL;
	t_lpass_error	err;
	t_entry **entries = entry_search( vault, "google", &err );
	cr_assert_eq( entries, NULL );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( entry_search, null_query_returns_error ) {
	t_lpass_error	err;
	t_entry **entries = entry_search( &vault, NULL, &err );
	cr_assert_eq( entries, NULL );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( entry_search, empty_vault_returns_empty_list ) {
	t_vault	vault = fresh_vault();
	t_lpass_error	err;
	t_entry **entries = entry_search( &vault, "nothing", &err );
	cr_assert( entries != NULL );
	cr_assert( err == LPASS_OK );
}

Test( entry_search, empty_querry ) {
	t_lpass_error	err;
	t_entry **entries = entry_search( &vault, "", &err );
	cr_assert_eq( entries, NULL );
	cr_assert( err == LPASS_ERR_NOT_FOUND );
}

Test( entry_search, no_match_returns_empty_list ) {
	t_lpass_error	err;
	t_entry **entries = entry_search( &vault, "helloworld", &err );
	cr_assert( entries != NULL );
	cr_assert( err == LPASS_OK );
}

Test( entry_search, single_match ) {
	t_lpass_error	err;
	t_entry **entries = entry_search( &vault, "github", &err );
	cr_assert_not_null( entries );
	cr_assert_str_eq( entries[ 0 ]->label, "github" );
	cr_assert( err == LPASS_OK );
	free( entries );
}

Test( entry_search, multiple_matches ) {
	t_lpass_error	err;
	t_entry **entries = entry_search( &vault, "google", &err );
	cr_assert_not_null( entries );
	cr_assert_not_null( entries[ 0 ] );
	cr_assert_not_null( entries[ 1 ] );
	cr_assert_str_eq( entries[ 0 ]->username, "ftleo" );
	cr_assert_str_eq( entries[ 1 ]->username, "ccleo" );
	cr_assert( err == LPASS_OK );
	free( entries );
}
