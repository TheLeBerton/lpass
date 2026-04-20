#include "structures.h"
#include "core.h"

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <criterion/parameterized.h>
#include <stdint.h>


Test( derive_key, happy_path ) {
	uint8_t	salt[ 32 ] = { 0 };
	uint8_t key[ 32 ];
	t_lpass_error err = derive_key( "password", salt, key );
	cr_assert( err == LPASS_OK );
}

Test( derive_key, same_inputs_same_key ) {
	uint8_t	salt[ 32 ] = { 0 };
	uint8_t key1[ 32 ], key2[ 32 ];
	derive_key( "password", salt, key1 );
	derive_key( "password", salt, key2 );
	cr_assert( memcmp( key1, key2, 32 ) == 0 );
}

Test( derive_key, different_salt_different_key ) {
	uint8_t	salt1[ 32 ] = { 0 };
	uint8_t	salt2[ 32 ] = { 1 };
	uint8_t key1[ 32 ], key2[ 32 ];
	derive_key( "password", salt1, key1 );
	derive_key( "password", salt2, key2 );
	cr_assert( memcmp( key1, key2, 32 ) != 0 );
}
