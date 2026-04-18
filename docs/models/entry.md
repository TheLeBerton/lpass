# Entry

An `Entry` is a stored account/information in the vault.


## Methods

### `entry_create`

Creates a new entry in the vault and returns it.

```c
t_entry  *entry_create( t_vault *vault, t_entry_params *params, t_lpass_error *err );
```


 | *err | return | condition |
 |----|------|---------|
 | `LPASS_OK` | entry | success |
 | `LPASS_ERR_NULL` | NULL | `vault` or `params` `NULL` |
 | `LPASS_WARN_EMPTY` | NULL | required field is empty |
 | `LPASS_ERR_MEMORY` | NULL | allocation failed |


---

### `entry_get`

 Returns the first entry found in the `vault` with `label`.

```c
t_entry  *entry_get( t_vault *vault, char *label, t_lpass_error *err );
```


 | *err | return | condition |
 |----|------|---------|
 | `LPASS_OK` | entry | success |
 | `LPASS_WARN_NOT_FOUND` | NULL | entry with `label` not in `vault` |
 | `LPASS_ERR_NULL` | NULL | `vault` or `label` `NULL` |


---

### `entry_search`

Returns a list of all entries with `query` as `label`, `url` or `username` in the `vault`.


```c
t_entry  **entry_search( t_vault *vault, char *query, t_lpass_error *err );
```


 | *err | return | condition |
 |----|------|---------|
 | `LPASS_OK` | **entries | success |
 | `LPASS_ERR_NULL` | NULL | `vault` or `query` `NULL` |
 | `LPASS_WARN_NOT_FOUND` | NULL | empty `query` |
 | `LPASS_ERR_MEMORY` | NULL | allocation failed |


 ---

### `entry_update`

Finds an entry with `label` in the `vault` and updates it with `new_data`.

```c
t_lpass_error  entry_update( t_vault *vault, char *label, t_entry_params *new_data );
```


 | return | condition |
 |------|---------|
 | `LPASS_OK` | success |
 | `LPASS_ERR_NULL` | `vault`, `label` or `new_data` `NULL` |
 | `LPASS_WARN_NOT_FOUND` | `label` not found in `vault.entries` |


---

### `entry_delete`

Deletes the first entry found with `label` in the `vault`.

```c
t_lpass_error  entry_delete( t_vault *vault, char *label );
```


 | return | condition |
 |------|---------|
 | `LPASS_OK` | success |
 | `LPASS_ERR_NULL` | `vault` or `label` `NULL` |
 | `LPASS_WARN_EMPTY` | empty `vault.entries` |
 | `LPASS_WARN_NOT_FOUND` | `label` not found in `vault.entries` |
 | `LPASS_ERR_MEMORY` | allocation failed |


