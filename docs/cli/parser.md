# Parser

The parser resolves the CLI arguments into a `t_args` struct.

```c
t_lpass_error  parse_args( int argc, char **argv, t_args *args );
```

## Arguments

Takes `argc` and `argv` from main, and a pointer to a fresh `t_args` variable.

## Behaviour

- Command matching is case-insensitive (`init`, `INIT`, `Init` all work).
- Commands that require an argument (`get`, `copy`, `delete`) return `LPASS_ERR_ARGS_MISSING` if the argument is absent or empty.
- Commands that do not require an argument (`init`, `add`, `list`, `gen`) ignore a third argv token — `argc > 3` is rejected before command matching.

## Returns

| reason | err | `t_args` |
|--------|-----|----------|
| `argc < 2` | `LPASS_ERR_ARGS_MISSING` | unchanged |
| `argc > 3` | `LPASS_ERR_ARGS_INVALID` | unchanged |
| unknown command | `LPASS_ERR_ARGS_INVALID` | `args.cmd = LPASS_CMD_UNKNOWN` |
| missing/empty argument for `get`, `copy`, `delete` | `LPASS_ERR_ARGS_MISSING` | `args.cmd` set |
| `strdup` failed | `LPASS_ERR_MEMORY` | `args.cmd` set |
| success | `LPASS_OK` | `args.cmd` set, `args.argument = NULL` or heap `char *` |
