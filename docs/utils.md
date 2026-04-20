# Utils

General utility functions.

## Methods

```c
void    generate_uuid( char *out );
```
> Generates a UUID v4 from `/dev/urandom` and writes it into `out`. Buffer must be at least 37 bytes.
