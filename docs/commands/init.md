# cmd_init

The `cmd_init` is the method used for the `LPASS_CMD_INIT`.

## Responsability

- Initializes the vault
- creates `~/.lpass/vault`
- generates `salt`
- saves the vault
- derives the key

## Return values


| Code | Cause |
|------|-------|
| LPASS_ERR_ALREADY_EXISTS | vault already present |
| LPASS_ERR_NULL | `HOME` not defined or stdin closed |
| LPASS_ERR_FILE | unable to write on the disk |
| LPASS_ERR_ARGS_INVALID | passwords do not match |
| LPASS_ERR_MEMORY | Argon2id - insufficient memory |
| LPASS_OK | success |

