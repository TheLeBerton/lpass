# LPASS
A local password manager written in C for Linux.


## Tech Stack
- **Language:** C
- **Encryption:** libsodium (XChaCha20-Poly1305 + Argon2id)
- **Autofill:** ydotool, xclip / wl-clipboard
- **Browser extension:** JS (Native Messaging)


## Goals
- Encrypt/Decrypt/Store passwords locally
- Autofill terminal (SSH)
- Autofill browsers (Firefox, Chrome)


## Out of Scope
- Cloud sync
- Autofill system apps (GTK/Qt)
- Mobile


## Vault

### Stored Fields
- label (entry name)
- url
- username
- password
- notes
- created_at
- updated_at

### Encryption
- libsodium — XChaCha20-Poly1305
- Argon2id — master password → 256 bit key


## Autofill

### Terminal
- ssh-agent integration — lpass loads SSH keys automatically
- clipboard fallback — for everything else

### Browsers
- JS extension detects `<input type="password">`
- Native Messaging to communicate with the C vault
- Automatic autofill if one account for the site, popup to choose if multiple


## CLI
```
lpass init              # create vault, set master password
lpass add               # add an entry
lpass get <label>       # display password in terminal
lpass list              # list all entries
lpass delete <label>    # delete an entry
lpass edit <label>      # edit an entry
lpass search <query>    # search by label/url/username
lpass copy <label>      # copy password to clipboard
lpass type <label>      # type password via ydotool
lpass gen               # generate a random password
lpass lock              # lock the vault manually
lpass unlock            # unlock the vault
lpass ssh add <label>   # load an SSH key into ssh-agent
```


## Security

### Master Password
- Minimum 12 characters
- Must be typed twice at creation
- Can be changed

### Automatic Lock
- Lock after X minutes of inactivity
- Lock when session closes

### Memory
- `mlock()` — secrets never written to swap
- `sodium_memzero` — wipe secrets from RAM after use

### Brute Force Protection
- Block after X failed attempts
- Progressive delay after block

### Clipboard
- Auto-clear after 30 seconds

### Password Generation
- Configurable length
- Upper/lowercase letters, numbers, special characters
