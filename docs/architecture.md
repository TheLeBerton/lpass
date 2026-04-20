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

Negative codes = critical errors. Positive codes = expected conditions.

## Modules

| File | Responsibility |
|------|---------------|
| `srcs/crypto/crypto.c` | Key derivation (`derive_key`, `generate_salt`) |
| `srcs/ui/prompt.c` | Terminal UI — password prompt with echo hide |
| `srcs/fs/file_system.c` | Filesystem helpers (`init_lpass_dir`) |
| `srcs/cli/parser.c` | CLI argument parsing |
| `srcs/cli/error_handler.c` | Error message printing |
| `srcs/commands/init.c` | `cmd_init` orchestration |
| `srcs/vault/vault.c` | Vault file I/O + memory allocation (save/load) |
| `srcs/vault/vault_helpers.c` | Binary serialization/deserialization |
| `srcs/vault/entry.c` | Entry CRUD |
| `srcs/vault/entry_helpers.c` | Internal helpers for entry operations |
| `srcs/utils.c` | UUID generation |
