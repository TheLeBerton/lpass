#ifndef UI_H
# define UI_H

# include "structures.h"

/**
 * @brief Prompts for a master password with double confirmation (echo hidden).
 * Used by cmd_init. Returns LPASS_ERR_ARGS_INVALID if the two entries differ.
 */
t_lpass_error	prompt_password( char *out, size_t size ) ;

/**
 * @brief Prompts for the master password once, no confirmation (echo hidden).
 * Used by commands that need to re-encrypt the vault.
 */
t_lpass_error	prompt_master_password( char *out, size_t size ) ;

/**
 * @brief Interactively fills a t_entry_params by prompting each field.
 * Prompts label, URL, username, password (echo hidden), and notes in order.
 */
t_lpass_error	prompt_add( t_entry_params *params ) ;

#endif
