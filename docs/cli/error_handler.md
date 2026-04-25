# Error handler

Prints error messages to stderr based on the error code returned by each subsystem.

## Methods

```c
void  error_handler_args( t_lpass_error err );
```
> Called when `parse_args` fails. Prints the error and correct usage, except for `LPASS_ERR_MEMORY` (no usage printed).

```c
void  error_handler_init( t_lpass_error err );
```
> Called when `cmd_init` fails. Handles `LPASS_ERR_ALREADY_EXISTS`, `LPASS_ERR_ARGS_INVALID`, `LPASS_ERR_NULL`, `LPASS_ERR_MEMORY`.

```c
void  error_handler_copy( t_lpass_error err );
```
> Called when `cmd_copy` fails. Handles `LPASS_ERR_MEMORY`, `LPASS_ERR_NULL`, `LPASS_WARN_NOT_FOUND`.

```c
void  error_handler_delete( t_lpass_error err );
```
> Called when `cmd_delete` fails. Handles `LPASS_ERR_MEMORY`, `LPASS_ERR_NULL`, `LPASS_WARN_NOT_FOUND`.
