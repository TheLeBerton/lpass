# cmd_get

Implements `LPASS_CMD_GET` — prints all fields of a single entry to stdout.

## Responsibility

1. `entry_get` — finds the entry matching `label` in the vault
2. Prints `label`, `url`, `username`, and `notes` (password is intentionally omitted)

## Signature

```c
t_lpass_error  cmd_get( t_vault *vault, char *label );
```

## Output format

```
Label: <label>
URL: <url>
Username: <username>
Notes: <notes>
```

## Return values

| Code | Cause |
|------|-------|
| `LPASS_OK` | success |
| `LPASS_ERR_NULL` | `vault` or `label` NULL |
| `LPASS_WARN_NOT_FOUND` | no entry with `label` in vault |
