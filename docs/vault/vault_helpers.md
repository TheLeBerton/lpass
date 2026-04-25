# vault_helpers

Internal helpers used by `vault.c` for serialization and deserialization. All functions are prefixed with `_` and not exposed in the public API.

## Serialization (save)

### `_validate_save_params`

Checks that `vault` and `path` are non-NULL and that `path` is non-empty.

```c
t_lpass_error  _validate_save_params( t_vault *vault, char *path );
```

---

### `_serialize_entries`

Serializes `vault->entries` into an encrypted ciphertext buffer using XChaCha20-Poly1305.

Plaintext layout: `[ entry_count : 4 ][ entries : N * sizeof(t_entry) ]`

```c
t_lpass_error  _serialize_entries( t_vault *vault, uint8_t *key,
                                   unsigned char **cipher, size_t *cipher_len );
```

| return | condition |
|--------|-----------|
| `LPASS_OK` | success |
| `LPASS_ERR_MEMORY` | allocation failed |

---

### `_serialize_vault`

Writes the full vault to an open file in the format: `[ salt : 32 ][ nonce : 24 ][ ciphertext_len : 8 ][ ciphertext ]`.

```c
t_lpass_error  _serialize_vault( t_vault *vault, FILE *f, uint8_t *key );
```

| return | condition |
|--------|-----------|
| `LPASS_OK` | success |
| `LPASS_ERR_MEMORY` | allocation failed |
| `LPASS_ERR_FILE` | write error |

---

## Deserialization (load)

### `_validate_load_params`

Checks that `vault` and `path` are non-NULL and that `path` is non-empty.

```c
t_lpass_error  _validate_load_params( t_vault **vault, char *path );
```

---

### `_deserialize_vault`

Orchestrates vault loading from an open file:

1. `_read_vault_header` — reads salt, nonce, and ciphertext from file
2. `_decrypt_entries` — re-derives the key with Argon2id, decrypts with XChaCha20-Poly1305
3. `_parse_entries` — copies decrypted bytes into `vault->entries`

```c
t_lpass_error  _deserialize_vault( t_vault *v, FILE *f, char *password );
```

| return | condition |
|--------|-----------|
| `LPASS_OK` | success |
| `LPASS_ERR_MEMORY` | allocation or Argon2id failure |
| `LPASS_ERR_FILE` | read error or wrong password (MAC verification failed) |
