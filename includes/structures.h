#ifndef STRUCTURES_H
# define STRUCTURES_H

#include <stdint.h>
#include <time.h>

typedef enum	e_lpass_error {
	LPASS_OK				=  0,
	LPASS_WARN_NOT_FOUND	=  1,
	LPASS_WARN_EMPTY		=  2,
	LPASS_ERR_NULL			= -1,
	LPASS_ERR_MEMORY		= -2,
}	t_lpass_error;

typedef struct s_entry_params {
	char	label[ 128 ];
	char	url[ 256 ];
	char	username[ 128 ];
	char	password[ 256 ];
	char	notes[ 1024 ];
} t_entry_params ;

typedef struct	s_entry {
	char	id[ 37 ];
	char	label[ 128 ];
	char	url[ 256 ];
	char	username[ 128 ];
	char	password[ 256 ];
	char	notes[ 1024 ];
	time_t	created_at;
	time_t	updated_at;
}	t_entry ;


typedef struct	s_vault {
	uint32_t	version;
	uint8_t		salt[ 32 ];
	uint8_t		nonce[ 24 ];
	uint32_t	entry_count;
	t_entry		*entries;
}	t_vault ;


#endif

