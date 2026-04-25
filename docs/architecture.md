# Architecture

## File Structure

```
includes/       — public headers (API declarations)
srcs/           — implementations
srcs/vault/     — vault and entry logic
tests/          — Criterion test suites (one file per function)
docs/           — project documentation
```

## Public Types

Defined in `includes/structures.h`.

### `t_vault`
Top-level container. Holds a flat `t_entry *entries` array (heap-allocated, grown with `realloc` on each insert), `entry_count`, and crypto fields (`salt`, `nonce`, `version`).

### `t_entry`
A single password record with a UUID v4 `id` (37 bytes), fixed-size char fields, and `created_at`/`updated_at` timestamps.

### `t_entry_params`
Input-only struct for creating or updating entries — no `id`, no timestamps.

### `t_lpass_error`
Enum used as return type for all fallible functions.

| Value | Code | Meaning |
|-------|------|---------|
| `LPASS_OK` | 0 | Success |
| `LPASS_WARN_NOT_FOUND` | 1 | Expected — entry not found |
| `LPASS_WARN_EMPTY` | 2 | Expected — empty input or vault |
| `LPASS_ERR_NULL` | -1 | Critical — NULL pointer passed |
| `LPASS_ERR_MEMORY` | -2 | Critical — allocation failed |
| `LPASS_ERR_FILE` | -3 | Critical — file I/O error |
| `LPASS_ERR_ARGS_INVALID` | -4 | Critical — invalid CLI argument or passwords don't match |
| `LPASS_ERR_ARGS_MISSING` | -5 | Critical — missing required CLI argument |
| `LPASS_ERR_ALREADY_EXISTS` | -6 | Critical — entry or vault already exists |

Negative codes = critical errors. Positive codes = expected conditions.

## Modules

| File | Responsibility |
|------|---------------|
| `srcs/crypto/crypto.c` | Key derivation (`derive_key`, `generate_salt`, `generate_nonce`) |
| `srcs/ui/prompt.c` | Terminal UI — password prompt, add prompt |
| `srcs/fs/file_system.c` | Filesystem helpers (`init_lpass_dir`, `get_vault_path`) |
| `srcs/cli/parser.c` | CLI argument parsing |
| `srcs/cli/error_handler.c` | Error message printing |
| `srcs/commands/init.c` | `cmd_init` — vault initialization |
| `srcs/commands/add.c` | `cmd_add` — add an entry |
| `srcs/commands/get.c` | `cmd_get` — display an entry |
| `srcs/commands/list.c` | `cmd_list` — list all entries |
| `srcs/commands/copy.c` | `cmd_copy` — copy password to clipboard |
| `srcs/commands/delete.c` | `cmd_delete` — delete an entry |
| `srcs/commands/gen.c` | `cmd_gen` — generate a random password |
| `srcs/commands/handler.c` | `handle_cmd` — command dispatch via policy table |
| `srcs/vault/vault.c` | Vault file I/O + memory allocation (save/load) |
| `srcs/vault/vault_helpers.c` | Binary serialization/deserialization |
| `srcs/vault/entry.c` | Entry CRUD |
| `srcs/vault/entry_helpers.c` | Internal helpers for entry operations |
| `srcs/utils.c` | UUID generation |
