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

void	setup( void ) {
	vault = fresh_vault();
}

void	teardown( void ) {
	free( vault.entries );
}

TestSuite( entry_create, .init = setup, .fini = teardown );

Test( entry_create, single_entry_incrment_count ) {
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "blabla" };
	t_lpass_error	err;
	entry_create( &vault, &params, &err );
	cr_assert( vault.entry_count == 1 );
}

Test( entry_create, multiple_entries_increment_count ) {
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "" };
	t_entry_params	params2 = { "google", "google.com", "ftleo", "123", "" };
	t_lpass_error	err;
	entry_create( &vault, &params, &err );
	entry_create( &vault, &params2, &err );
	cr_assert( vault.entry_count == 2 );
	cr_assert_str_eq( vault.entries[ 0 ].label, "github" );
	cr_assert_str_eq( vault.entries[ 1 ].label, "google" );
}

Test( entry_create, returns_entry_on_success ) {
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "blabla" };
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, &params, &err );
	cr_assert_not_null( entry );
	cr_assert_eq( err, LPASS_OK );
}

Test( entry_create, copies_all_fields ) {
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "blabla" };
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, &params, &err );
	cr_assert( entry->id[0] != '\0' );
	cr_assert_str_eq( entry->label, "github" );
	cr_assert_str_eq( entry->url, "github.com" );
	cr_assert_str_eq( entry->username, "ftleo" );
	cr_assert_str_eq( entry->password, "123" );
	cr_assert_str_eq( entry->notes, "blabla" );
	cr_assert( entry->created_at != 0 );
	cr_assert( entry->updated_at != 0 );
	cr_assert_eq( err, LPASS_OK );
}

Test( entry_create, null_vault_returns_error ) {
	t_vault	*vault = NULL;
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "blabla" };
	t_lpass_error	err;
	t_entry	*entry = entry_create( vault, &params, &err );
	cr_assert_null( entry );
	cr_assert_eq( err, LPASS_ERR_NULL );
}

Test( entry_create, null_params_returns_error ) {
	t_entry_params	*params = NULL;
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, params, &err );
	cr_assert_null( entry );
	cr_assert_eq( err, LPASS_ERR_NULL );
}

Test( entry_create, empty_notes_is_allowed ) {
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "" };
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, &params, &err );
	cr_assert_not_null( entry );
	cr_assert_eq( err, LPASS_OK );
}

Test( entry_create, uuid_has_valid_format ) {
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "" };
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, &params, &err );
	cr_assert( strlen( entry->id ) == 36 );
	cr_assert( entry->id[ 8 ] == '-' );
	cr_assert( entry->id[ 13 ] == '-' );
	cr_assert( entry->id[ 18 ] == '-' );
	cr_assert( entry->id[ 23 ] == '-' );
}

Test( entry_create, label_at_max_length ) {
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "" };
	memset( params.label, 'a', sizeof( params.label ) - 1 );
	params.label[ sizeof( params.label ) - 1 ] = '\0';
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, &params, &err );
	cr_assert( strlen( entry->label ) == 127 );
}

struct create_invalid_case {
	t_entry_params	params;
	t_lpass_error	expected_err;
};

ParameterizedTestParameters( entry_create, empty_required_field_returns_error ){
	static struct create_invalid_case	cases[] = {
		{ { "", "github.com", "ftleo", "123", "blabla" }, LPASS_ERR_EMPTY },
		{ { "github", "", "ftleo", "123", "blabla" }, LPASS_ERR_EMPTY },
		{ { "github", "github.com", "ftleo", "", "blabla" }, LPASS_ERR_EMPTY },
		{ { "github", "github.com", "", "123", "blabla" }, LPASS_ERR_EMPTY },
	};
	size_t	count = sizeof( cases ) / sizeof( cases[ 0 ] );
	return ( cr_make_param_array( struct create_invalid_case, cases, count, NULL ) );
}

ParameterizedTest( struct create_invalid_case *tc, entry_create, empty_param ) {
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, &tc->params, &err );
	cr_assert_null( entry );
	cr_assert_eq( err, tc->expected_err );
}

