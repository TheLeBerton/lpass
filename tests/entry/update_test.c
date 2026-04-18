#include "structures.h"
#include "entry.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <criterion/parameterized.h>
#include <time.h>

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

TestSuite( entry_update, .init = setup, .fini = teardown );

Test( entry_update, null_vault_returns_error ) {
	t_entry_params	new_data = { 0 };
	t_lpass_error	err = entry_update( NULL, "github", &new_data );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( entry_update, null_label_returns_error ) {
	t_entry_params	new_data = { 0 };
	t_lpass_error	err = entry_update( &vault, NULL, &new_data );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( entry_update, null_new_data_returns_error ) {
	t_lpass_error	err = entry_update( &vault, "github", NULL );
	cr_assert( err == LPASS_ERR_NULL );
}

Test( entry_update, not_found_returns_error ) {
	t_entry_params	new_data = { 0 };
	t_lpass_error	err = entry_update( &vault, "nothinginthere", &new_data );
	cr_assert( err == LPASS_WARN_NOT_FOUND );
}

Test( entry_update, updates_fields_correctly ) {
	t_entry_params	new_data = { 0 };
	strlcpy( new_data.username, "new_username", sizeof( new_data.username ) );
	strlcpy( new_data.password, "new_password", sizeof( new_data.password ) );
	strlcpy( new_data.notes, "new_notes", sizeof( new_data.notes ) );
	t_lpass_error	err = entry_update( &vault, "github", &new_data );
	cr_assert( err == LPASS_OK );
	cr_assert_str_eq( vault.entries[ 0 ].username, "new_username" );
	cr_assert_str_eq( vault.entries[ 0 ].password, "new_password" );
	cr_assert_str_eq( vault.entries[ 0 ].notes, "new_notes" );
}

Test( entry_update, updates_updated_at_timestamp ) {
	t_entry_params	new_data = { 0 };
	strlcpy( new_data.username, "new_username", sizeof( new_data.username ) );
	time_t	now = time( NULL );
	t_lpass_error	err = entry_update( &vault, "github", &new_data );
	cr_assert( err == LPASS_OK );
	cr_assert( vault.entries[ 0 ].updated_at >= now );
}
