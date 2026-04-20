# cmd_init

The `cmd_init` is the method used for the `LPASS_CMD_INIT`.

## Responsability

Orchestrates vault initialization in order:

1. `init_lpass_dir` — creates `~/.lpass/`, checks vault doesn't exist, returns path
2. `prompt_password` — prompts and confirms master password
3. `generate_salt` — fills `vault->salt` with random bytes
4. `derive_key` — derives 32-byte key from password + salt
5. `vault_save` — writes vault to disk

## Return values


| Code | Cause |
|------|-------|
| LPASS_ERR_ALREADY_EXISTS | vault already present |
| LPASS_ERR_NULL | `HOME` not defined or stdin closed |
| LPASS_ERR_FILE | unable to write on the disk |
| LPASS_ERR_ARGS_INVALID | passwords do not match |
| LPASS_ERR_MEMORY | Argon2id - insufficient memory |
| LPASS_OK | success |

