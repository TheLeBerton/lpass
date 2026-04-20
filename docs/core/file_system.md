# File System

Filesystem helpers for lpass directory management.

## Methods

```c
t_lpass_error   init_lpass_dir( char *path, size_t size );
```
> Creates `~/.lpass/` if needed, checks that the vault doesn't already exist, and writes the vault path into `path`.

| return | condition |
|--------|-----------|
| `LPASS_OK` | success — `path` is populated |
| `LPASS_ERR_NULL` | `HOME` environment variable not set |
| `LPASS_ERR_ALREADY_EXISTS` | vault file already present |
