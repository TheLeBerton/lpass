# Goals

What "done" looks like for lpass v1.0.

## Implemented commands

| Command | Acceptance criteria |
|---------|---------------------|
| `lpass init` | Creates `~/.lpass/vault`, fails if vault already exists, master password confirmed twice |
| `lpass add` | Prompts all fields, rejects duplicates, persists encrypted vault |
| `lpass get <label>` | Prints label, URL, username, notes — never prints password |
| `lpass list` | Prints label, URL, username for every entry |
| `lpass copy <label>` | Copies password to clipboard via xclip, exits cleanly |
| `lpass delete <label>` | Removes entry, persists encrypted vault |
| `lpass gen [length]` | Prints a random password with digits, lower, upper, symbols — shuffled |

## Quality criteria

- Every command exits with code 0 on success, non-zero on error.
- Errors are printed to stderr with a clear message.
- The master password is never stored in plaintext — it is zeroed after key derivation.
- The vault is re-encrypted on every write with a fresh nonce.
- All public API functions are covered by Criterion tests.

## Out of scope for v1.0

- `lpass edit` — edit an existing entry
- `lpass search` — search across label/URL/username
- `lpass type` — type password via ydotool
- Browser autofill (Native Messaging extension)
- SSH agent integration
- Vault lock/unlock
