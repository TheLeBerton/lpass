# cmd_add

Implements `LPASS_CMD_ADD` — interactively prompts for a new entry and persists it to the vault.

## Responsibility

Orchestrates entry creation in order:

1. `prompt_add` — prompts the user for label, URL, username, password, notes
2. `entry_create` — validates params and appends the entry to `vault->entries`
3. `prompt_master_password` — asks for the master password to re-encrypt
4. `derive_key` — derives the 32-byte key from password + `vault->salt`
5. `get_vault_path` — resolves `~/.lpass/vault`
6. `vault_save` — encrypts and writes the vault to disk

## Signature

```c
t_lpass_error  cmd_add( t_vault *vault, char *label );
```

`label` is unused — entry fields are collected interactively via `prompt_add`.

## Return values

| Code | Cause |
|------|-------|
| `LPASS_OK` | success |
| `LPASS_ERR_NULL` | `vault` NULL, or `HOME` not defined |
| `LPASS_WARN_EMPTY` | required field left blank |
| `LPASS_ERR_ALREADY_EXISTS` | entry with same label already in vault |
| `LPASS_ERR_MEMORY` | allocation or Argon2id failure |
| `LPASS_ERR_FILE` | vault could not be written to disk |
