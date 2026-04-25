# Prompt

Terminal UI for user input — hides echo for password fields.

## Methods

```c
t_lpass_error  prompt_password( char *out, size_t size );
```
> Prompts for a master password twice (with confirmation). Returns `LPASS_ERR_ARGS_INVALID` if the two entries don't match. Used by `cmd_init`.

| return | condition |
|--------|-----------|
| `LPASS_OK` | success |
| `LPASS_ERR_NULL` | stdin closed |
| `LPASS_ERR_ARGS_INVALID` | passwords do not match |

---

```c
t_lpass_error  prompt_master_password( char *out, size_t size );
```
> Prompts for the master password once (no confirmation, echo hidden). Used by `cmd_add`, `cmd_delete`, and any command that needs to re-encrypt the vault.

| return | condition |
|--------|-----------|
| `LPASS_OK` | success |
| `LPASS_ERR_NULL` | stdin closed |

---

```c
t_lpass_error  prompt_add( t_entry_params *params );
```
> Interactively fills a `t_entry_params` by prompting for label, URL, username, password (echo hidden), and notes. Used by `cmd_add`.

| return | condition |
|--------|-----------|
| `LPASS_OK` | success |
| `LPASS_ERR_NULL` | stdin closed during any field |
