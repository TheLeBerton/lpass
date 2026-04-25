# cmd_gen

Implements `LPASS_CMD_GEN` — generates a random password and prints it to stdout.

## Responsibility

Generates a password of `n` characters (default 20, minimum 4) using `libsodium`'s `randombytes_uniform`.
Guarantees at least one character from each class: digit, lowercase, uppercase, symbol (`!@#$^&*?`).
The result is then shuffled with a Fisher-Yates pass driven by `randombytes_uniform`.

## Signature

```c
t_lpass_error  cmd_gen( t_vault *vault, char *label );
```

`label` is repurposed as the desired length (parsed with `atoi`). `vault` is unused.

## Return values

| Code | Cause |
|------|-------|
| `LPASS_OK` | always — password is printed to stdout |
