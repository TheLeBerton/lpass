#include "structures.h"
#include "entry.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/parameterized.h>

struct create_invalid_case {
	t_entry_params	params;
	t_lpass_error	expected_err;
};

ParameterizedTestParameters( entry, create_invalid ){
	static struct create_invalid_case	cases[] = {
		{ { "", "github.com", "ftleo", "123", "blabla" }, LPASS_ERR_EMPTY },
		{ { "github", "", "ftleo", "123", "blabla" }, LPASS_ERR_EMPTY },
		{ { "github", "github.com", "ftleo", "", "blabla" }, LPASS_ERR_EMPTY },
		{ { "github", "github.com", "", "123", "blabla" }, LPASS_ERR_EMPTY },
	};
	size_t	count = sizeof( cases ) / sizeof( cases[ 0 ] );
	return ( cr_make_param_array( struct create_invalid_case, cases, count, NULL ) );
}

ParameterizedTest( struct create_invalid_case *tc, entry, create_invalid ) {
	t_vault	vault = { 0 };
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, &tc->params, &err );
	cr_assert_null( entry );
	cr_assert_eq( err, tc->expected_err );
}

Test( entry, create ) {
	t_vault	vault = { 0 };
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "blabla" };
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, &params, &err );
	cr_assert_not_null( entry );
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

Test( entry, create_vault_is_null ) {
	t_vault	*vault = NULL;
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "blabla" };
	t_lpass_error	err;
	t_entry	*entry = entry_create( vault, &params, &err );
	cr_assert_null( entry );
	cr_assert_eq( err, LPASS_ERR_NULL );
}

Test( entry, create_params_is_null ) {
	t_vault	vault = { 0 };
	t_entry_params	*params = NULL;
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, params, &err );
	cr_assert_null( entry );
	cr_assert_eq( err, LPASS_ERR_NULL );
}

Test( entry, create_params_empty_notes ) {
	t_vault	vault = { 0 };
	t_entry_params	params = { "github", "github.com", "ftleo", "123", "" };
	t_lpass_error	err;
	t_entry	*entry = entry_create( &vault, &params, &err );
	cr_assert_not_null( entry );
	cr_assert_eq( err, LPASS_OK );
}
