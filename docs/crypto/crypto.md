# Crypto

Key derivation and salt generation using libsodium.

## Methods

```c
t_lpass_error   derive_key( const char *password, const uint8_t *salt, uint8_t *key );
```
> Derives a 32-byte encryption key from a password and a salt using Argon2id.

```c
void    generate_salt( uint8_t *salt, size_t size );
```
> Fills `salt` with `size` cryptographically random bytes.

```c
void    generate_nonce( uint8_t *nonce, size_t size );
```
> Fills `nonce` with `size` cryptographically random bytes. Must be called on each save.

