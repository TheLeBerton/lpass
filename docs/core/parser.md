# Parser

The parser is used to get the right command from the user at program launch.

```c
t_lpass_error	parse_args( int argc, char **argv, t_args *args ) ;
```

## Arguments

Takes in the `argc` and `argv` from main, and a pointer to a fresh `t_args` variable.


## Returns

| reason | err | `t_args` |
|-----|--------|----------|
| argc is bigger than 3 | LPASS_ERR_ARGS_INVALID | unchanged |
| argc is smaller than 2 | LPASS_ERR_ARGS_MISSING | unchanged |
| unknown command | LPASS_ERR_ARGS_INVALID | args.cmd: `LPASS_CMD_UNKNOWN` |
| missing or empty argument for `delete` and `copy` | LPASS_ERR_ARGS_MISSING | args.cmd: set to matched command |
| `strdup` failed | LPASS_ERR_MEMORY | args.cmd: set to matched command  |
| success | LPASS_OK | args.cmd: set to matched command , args.argument = `NULL` if not needed else `char *` |





