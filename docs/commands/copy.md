# cmd_copy

Implements `LPASS_CMD_COPY` — copies the password of an entry to the system clipboard.

## Responsibility

1. `entry_get` — finds the entry matching `label` in the vault
2. `_copy_to_clipboard` — pipes `entry->password` into `xclip -selection clipboard`

## Signature

```c
t_lpass_error  cmd_copy( t_vault *vault, char *label );
```

## Dependencies

Requires `xclip` to be installed on the system. Uses `popen` to write to the clipboard.

## Return values

| Code | Cause |
|------|-------|
| `LPASS_OK` | success |
| `LPASS_ERR_NULL` | `vault` or `label` NULL |
| `LPASS_WARN_NOT_FOUND` | no entry with `label` in vault |
| `LPASS_ERR_MEMORY` | `popen` failed to open the pipe |
