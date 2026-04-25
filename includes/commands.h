#ifndef COMMANDS_H
# define COMMANDS_H

# include "structures.h"

/**
 * @brief Dispatches args.cmd to the matching cmd_* function via a policy table.
 * Loads and frees the vault automatically for commands that need it.
 * @return Error code forwarded from the matched cmd_* function.
 */
t_lpass_error	handle_cmd( t_vault *vault, t_args args ) ;

#endif
