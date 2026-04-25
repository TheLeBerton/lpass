# cmd_list

Implements `LPASS_CMD_LIST` — prints label, URL, and username for every entry in the vault.

## Responsibility

Iterates over all entries via `entry_get` and prints a summary for each one.

## Signature

```c
t_lpass_error  cmd_list( t_vault *vault );
```

## Output format

For each entry:

```
Label: <label>
URL: <url>
Username: <username>

```

A blank line separates each entry.

## Return values

| Code | Cause |
|------|-------|
| `LPASS_OK` | success |
| `LPASS_ERR_NULL` | `vault` NULL |
| `LPASS_WARN_NOT_FOUND` | entry index inconsistency (label not found) |
