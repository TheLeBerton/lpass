#ifndef UTILS_H
# define UTILS_H

/**
 * @brief Generates a UUID v4 from /dev/urandom and writes it into out.
 * out must be at least 37 bytes (36 chars + null terminator).
 */
void	generate_uuid( char *out ) ;

#endif
