#ifndef CLI_H
# define CLI_H

# include "structures.h"

/**
 * @brief Parses argc/argv into a t_args struct.
 * Command matching is case-insensitive. Duplicates the argument with strdup if needed.
 * @return LPASS_OK on success, LPASS_ERR_ARGS_INVALID / LPASS_ERR_ARGS_MISSING on error.
 */
t_lpass_error	parse_args( int argc, char **argv, t_args *args ) ;

/**
 * @brief Prints the error from parse_args to stderr with usage hint.
 * Usage hint is omitted for LPASS_ERR_MEMORY.
 */
void			error_handler_args( t_lpass_error err ) ;

/**
 * @brief Prints the error from cmd_init to stderr.
 */
void			error_handler_init( t_lpass_error err ) ;

/**
 * @brief Prints the error from cmd_copy to stderr.
 */
void			error_handler_copy( t_lpass_error err ) ;

/**
 * @brief Prints the error from cmd_delete to stderr.
 */
void			error_handler_delete( t_lpass_error err ) ;

#endif
