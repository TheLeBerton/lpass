# Crypto

This module is used for all encryption/decryption methods in the project.

## Methods

```c
t_lpass_error   derive_key( const char *password, const uint8_t *salt, uint8_t *key );
```
> Derives a 32-byte encryption key from a password and a salt using Argon2id.

```c
t_lpass_error   prompt_password( char *out, size_t size );
```
> Prompts the user to enter and confirm a master password, hiding input from terminal.

