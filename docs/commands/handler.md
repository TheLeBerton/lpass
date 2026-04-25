# commands_handler

Dispatches the parsed command to the right `cmd_*` function via a policy table.

## Responsibility

`handle_cmd` iterates over `policies[]` to find the entry matching `args.cmd`.
If the policy has `needs_vault = 1`, it calls `_load_vault` first (prompt + decrypt).
Then it calls the associated function pointer with `(vault, args.argument)`.
After the call, it frees `vault->entries` and `vault` if a vault was loaded.

## Policy table

```c
typedef struct s_cmd_policy {
    t_command       cmd;
    t_lpass_error   (*fn)( t_vault *, char * );
    int             needs_vault;
} t_cmd_policy;
```

| Command | Function | needs_vault |
|---------|----------|-------------|
| `LPASS_CMD_INIT` | `cmd_init` | 0 |
| `LPASS_CMD_GEN` | `cmd_gen` | 0 |
| `LPASS_CMD_ADD` | `cmd_add` | 1 |
| `LPASS_CMD_GET` | `cmd_get` | 1 |
| `LPASS_CMD_LIST` | `cmd_list` | 1 |
| `LPASS_CMD_COPY` | `cmd_copy` | 1 |
| `LPASS_CMD_DEL` | `cmd_delete` | 1 |

## Signatures

```c
t_lpass_error  handle_cmd( t_vault *vault, t_args args );
```

## Return values

Forwards the return value of the matched `cmd_*` function, or `LPASS_OK` if no matching command is found.
