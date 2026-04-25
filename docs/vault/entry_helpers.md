# entry_helpers

Internal helpers used by `entry.c`. All functions are prefixed with `_` and not exposed in the public API.

## `_is_empty`

Returns `1` if `str` is an empty string, `0` otherwise.

```c
int  _is_empty( char *str );
```

---

## `_validate_params`

Validates that `vault` and `params` are non-NULL and that the required fields (`label`, `url`, `username`, `password`) are non-empty. Also checks that no entry with the same label already exists.

```c
t_lpass_error  _validate_params( t_vault *vault, t_entry_params *params );
```

| return | condition |
|--------|-----------|
| `LPASS_OK` | all checks pass |
| `LPASS_ERR_NULL` | `vault` or `params` NULL |
| `LPASS_WARN_EMPTY` | required field is empty |
| `LPASS_ERR_ALREADY_EXISTS` | entry with same label already in vault |

---

## `_alloc_entry`

Grows `vault->entries` by one slot via `realloc`.

```c
t_lpass_error  _alloc_entry( t_vault *vault );
```

| return | condition |
|--------|-----------|
| `LPASS_OK` | success |
| `LPASS_ERR_MEMORY` | `realloc` failed |

---

## `_init_entry`

Initializes a new `t_entry` from `params`, generating a UUID and setting `created_at` / `updated_at` to the current time.

```c
t_entry  _init_entry( t_entry_params *params );
```

---

## `_matches_queries`

Returns `1` if the entry at index `i` contains `query` (case-insensitive) in its `label`, `url`, or `username`.

```c
int  _matches_queries( t_vault *vault, char *query, uint32_t i );
```

---

## `_alloc_entries`

Grows a `t_entry **` result array to fit `count + 1` entries plus a NULL terminator.

```c
t_lpass_error  _alloc_entries( t_entry ***entries, int count );
```

| return | condition |
|--------|-----------|
| `LPASS_OK` | success |
| `LPASS_ERR_MEMORY` | `realloc` failed |
