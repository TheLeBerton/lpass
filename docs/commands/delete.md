# cmd_delete

Implements `LPASS_CMD_DEL` — deletes an entry from the vault by label then persists the vault.

## Responsibility

1. `entry_delete` — removes the entry matching `label` from the vault
2. `_save_entry` — prompts for the master password, derives the key, and calls `vault_save`

## Signature

```c
t_lpass_error  cmd_delete( t_vault *vault, char *label );
```

## Return values

| Code | Cause |
|------|-------|
| `LPASS_OK` | success |
| `LPASS_WARN_NOT_FOUND` | no entry with `label` in vault |
| `LPASS_ERR_NULL` | `vault` or `label` NULL |
| `LPASS_ERR_CRYPTO` | key derivation failed |
| `LPASS_ERR_FS` | vault path resolution or file write failed |
