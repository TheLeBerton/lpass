#include <stdint.h>
#include <stdio.h>


/**
 * @brief Generates a UUID v4 from /dev/urandom
 * @param out	output buffer, must be at least 37 bytes
 */
void	generate_uuid( char *out ) {
	FILE *file = fopen("/dev/urandom", "r");
	if ( !file )
		return ;
	uint8_t	bytes[ 16 ];
	fread( bytes, 1, 16, file );
	bytes[ 6 ] = ( bytes[ 6 ] & 0x0f ) | 0x40; // version 4
	bytes[ 8 ] = ( bytes[ 8 ] & 0x3f ) | 0x80; // variant RFC 4122
	snprintf( out, 37, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		bytes[ 0 ], bytes[ 1 ], bytes[ 2 ], bytes[ 3 ],
		bytes[ 4 ], bytes[ 5 ],
		bytes[ 6 ], bytes[ 7 ],
		bytes[ 8 ], bytes[ 9 ],
		bytes[ 10 ], bytes[ 11 ], bytes[ 12 ], bytes[ 13 ], bytes[ 14 ], bytes[ 15 ]
	) ;
	fclose( file );
}
