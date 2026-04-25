#ifndef ENTRY_H
# define ENTRY_H

#include "structures.h"

/**
 * @brief Creates a new entry in the vault.
 * Validates params, appends to vault->entries, sets UUID and timestamps.
 * @return Pointer to the new entry, or NULL on failure (*err set).
 */
t_entry			*entry_create( t_vault *vault, t_entry_params *params, t_lpass_error *err ) ;

/**
 * @brief Returns the first entry matching label (exact, case-sensitive).
 * @return Pointer to the entry, or NULL if not found (*err set).
 */
t_entry			*entry_get( t_vault *vault, char *label, t_lpass_error *err ) ;

/**
 * @brief Returns all entries whose label, url, or username contain query (case-insensitive).
 * The returned array is NULL-terminated. Caller owns the array, not the entries.
 * @return NULL-terminated array of entry pointers, or NULL on failure (*err set).
 */
t_entry			**entry_search( t_vault *vault, char *query, t_lpass_error *err ) ;

/**
 * @brief Updates an existing entry by label, refreshing updated_at.
 * @return LPASS_OK on success, LPASS_WARN_NOT_FOUND if label is absent.
 */
t_lpass_error	entry_update( t_vault *vault, char *label, t_entry_params *new_data ) ;

/**
 * @brief Deletes the first entry matching label, shifts remaining entries left.
 * @return LPASS_OK on success, LPASS_WARN_NOT_FOUND if label is absent.
 */
t_lpass_error	entry_delete( t_vault *vault, char *label ) ;


#endif
