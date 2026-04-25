# lpass

A local password manager written in C for Linux. Passwords are encrypted with XChaCha20-Poly1305 and a master password derived with Argon2id (libsodium). Nothing leaves your machine.

## Dependencies

| Dependency | Purpose |
|------------|---------|
| [libsodium](https://libsodium.org) | encryption and key derivation |
| [xclip](https://github.com/astrand/xclip) | `lpass copy` clipboard support |
| [Criterion](https://criterion.readthedocs.io) | test runner (optional) |

Install on Fedora/RHEL:
```sh
sudo dnf install libsodium-devel xclip
```

Install on Debian/Ubuntu:
```sh
sudo apt install libsodium-dev xclip
```

## Install

```sh
git clone https://github.com/TheLeBerton/lpass.git
cd lpass
make
make install     # installs to ~/.local/bin/lpass
```

Make sure `~/.local/bin` is in your `PATH`.

To uninstall:
```sh
make uninstall   # removes binary and ~/.lpass/
```

## Quickstart

```sh
# 1. Create the vault and set your master password
lpass init

# 2. Add a password
lpass add

# 3. View an entry
lpass get github

# 4. List all entries
lpass list

# 5. Copy a password to clipboard
lpass copy github

# 6. Delete an entry
lpass delete github

# 7. Generate a random password
lpass gen        # 20 chars (default)
lpass gen 32     # 32 chars
```

## Commands

| Command | Description |
|---------|-------------|
| `lpass init` | Create the vault and set the master password |
| `lpass add` | Add a new entry (interactive prompt) |
| `lpass get <label>` | Display an entry's fields |
| `lpass list` | List all entries (label, URL, username) |
| `lpass copy <label>` | Copy an entry's password to clipboard |
| `lpass delete <label>` | Delete an entry |
| `lpass gen [length]` | Generate a random password |

## Vault

The vault is stored at `~/.lpass/vault`. It is a binary file with the following layout:

```
[ salt : 32 bytes ][ nonce : 24 bytes ][ ciphertext_len : 8 bytes ][ ciphertext ]
```

The ciphertext contains `entry_count` followed by the raw entry array, encrypted with XChaCha20-Poly1305. The key is never stored — it is re-derived from the master password on each operation.

## Development

```sh
make          # build → ./lpass
make test     # build and run tests → ./test_runner
make re       # full rebuild
make clean    # remove object files
make fclean   # remove object files + binaries
```

Tests require [Criterion](https://criterion.readthedocs.io).
