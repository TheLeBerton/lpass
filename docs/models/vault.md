# Vault

A `vault` stores all informations about `entry`'s and encryption.

```c
typedef struct	s_vault {
	uint32_t	version;
	uint8_t		salt[ 32 ];
	uint8_t		nonce[ 24 ];
	uint32_t	entry_count;
	t_entry		*entries;
}	t_vault ;
```

## Methods

### `vault_save`

Saves a `vault` into a `path` in raw bytes.

```c
t_lpass_error	vault_save( t_vault *vault, char *path ) ;
```


 | return | condition |
 |------|---------|
 | `LPASS_OK` | success |
 | `LPASS_ERR_NULL` | `vault` or `path` `NULL` |
 | `LPASS_WARN_EMPTY` | empty `path` `str` |
 | `LPASS_ERR_FILE` | error opening / writing / closing `path` |


---

### `vault_load`

Loads a `vault` from a `path`.

```c
t_lpass_error	vault_load( t_vault **vault, char *path ) ;
```


 | return | condition |
 |------|---------|
 | `LPASS_OK` | success |
 | `LPASS_ERR_NULL` | `vault` or `path` `NULL` |
 | `LPASS_WARN_EMPTY` | empty `path` `str` |
 | `LPASS_ERR_MEMORY` | allocation failed |
 | `LPASS_ERR_FILE` | error opening / reading / closing `path` |

