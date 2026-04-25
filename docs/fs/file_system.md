# File System

Filesystem helpers for lpass directory and vault path management.

## Methods

```c
t_lpass_error  get_vault_path( char *path, size_t size );
```
> Creates `~/.lpass/` if it doesn't exist (mode 0700), then writes the vault path (`~/.lpass/vault`) into `path`.

| return | condition |
|--------|-----------|
| `LPASS_OK` | success — `path` is populated |
| `LPASS_ERR_NULL` | `HOME` environment variable not set |

---

```c
t_lpass_error  init_lpass_dir( char *path, size_t size );
```
> Calls `get_vault_path`, then checks that the vault file doesn't already exist. Used only by `cmd_init`.

| return | condition |
|--------|-----------|
| `LPASS_OK` | success — `path` is populated, vault absent |
| `LPASS_ERR_NULL` | `HOME` environment variable not set |
| `LPASS_ERR_ALREADY_EXISTS` | vault file already present |
