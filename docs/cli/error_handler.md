# Error handler

This "module" is used to handle all errors received in the `main`.

## Methods

Currently it only has one method.


```c
void	error_handler_args( t_lpass_error err ) ;
```
> This method is used if the return value of `parse_args()` is not `LPASS_OK`.
> Printing out the error message on stderr and correct usage.
> If the error is a `LPASS_ERR_MEMORY`, no correct usage will be printed

