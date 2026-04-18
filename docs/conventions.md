# Conventions

## API

- Public API declared in `includes/`, implemented in `srcs/`.
- Internal helpers prefixed with `_` and declared in a local header inside the module (e.g. `srcs/vault/entry_helpers.h`).
- Functions returning a pointer signal errors via a `t_lpass_error *err` out-parameter and return `NULL` on failure.
- Functions returning `t_lpass_error` directly use the return value as the error code.
- `entry_search` returns a NULL-terminated array of pointers into `vault->entries` — caller owns the pointer array but not the entries themselves.

## Error Handling

- `err < 0` — critical error (NULL pointer, memory failure, file I/O)
- `err > 0` — expected condition (not found, empty)
- `err == 0` — success

Always check `err` before using the return value.

## Testing

- One test file per function (`tests/entry/create_test.c`, etc.)
- Suite named after the function (`entry_create`, `entry_get`, etc.)
- `TestSuite` with `.init = setup` and `.fini = teardown` for automatic cleanup
- Helpers for setup state, manual `free()` only for non-standard allocations
- Test file paths use `mkstemp()` to avoid conflicts between parallel tests
