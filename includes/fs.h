#ifndef FS_H
# define FS_H

# include "structures.h"

/**
 * @brief Creates ~/.lpass/ (mode 0700) if absent, writes ~/.lpass/vault into path.
 * @return LPASS_OK on success, LPASS_ERR_NULL if HOME is not set.
 */
t_lpass_error	get_vault_path( char *path, size_t size ) ;

/**
 * @brief Calls get_vault_path then checks the vault file does not already exist.
 * Used exclusively by cmd_init.
 * @return LPASS_OK on success, LPASS_ERR_ALREADY_EXISTS if vault is present.
 */
t_lpass_error	init_lpass_dir( char *path, size_t size ) ;

#endif
