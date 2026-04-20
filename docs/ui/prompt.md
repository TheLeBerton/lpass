# Prompt

Terminal UI for password input — hides echo during input.

## Methods

```c
t_lpass_error   prompt_password( char *out, size_t size );
```
> Prompts the user to enter and confirm a master password. Returns `LPASS_ERR_ARGS_INVALID` if the two entries don't match.

| return | condition |
|--------|-----------|
| `LPASS_OK` | success |
| `LPASS_ERR_NULL` | stdin closed |
| `LPASS_ERR_ARGS_INVALID` | passwords do not match |
