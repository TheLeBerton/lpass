#ifndef FS_H
# define FS_H

# include "structures.h"

t_lpass_error	get_vault_path( char *path, size_t size ) ;
t_lpass_error	init_lpass_dir( char *path, size_t size ) ;

#endif
