/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_splitter_internal.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:21:30 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:17:26 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFINED_SPLITTER_INTERNAL_H
# define REFINED_SPLITTER_INTERNAL_H

# include "../../../../data_structures/data_structures.h"
# include "../../lexer_internal.h"
# include "../splitter_internal.h"
# include "../raw_splitter/raw_splitter.h"

/**
 * # t_refine_raw_token_vars
 *
 * Internal variables used during the
 * refinement of a raw token.
 * Maintains parsing state: current
 * position, accumulated buffer,
 * quote tracking, and new token limits.
 *
 * Key fields:
 * - `new_token`: temporary buffer where
 *   the refined token is built.
 * - `idx` / `idx_new_token`: indices of
 *   the original and refined token.
 * - `found_quote`: indicates if we are
 *   inside a quote.
 * - `last_start`: absolute coordinate of
 *   the start of a grouped slice.
 */
typedef struct s_refine_raw_token_params	t_refine_raw_token_vars;
struct s_refine_raw_token_params
{
	char	*new_token;
	int		idx_new_token;
	int		idx;
	int		found_quote;
	int		token_len;
	int		last_start;
};

/**
 * # t_refined_token_push_params
 *
 * Scope structure used when inserting
 * refined tokens into the list.
 * Contains: raw token, original position,
 * partial buffer, and the array that
 * will receive the new chunks.
 *
 * Passed to specialized push functions.
 */
typedef struct s_refined_token_push_params	t_refined_token_push_params;
struct s_refined_token_push_params
{
	t_linkedlist_array		*refineds;
	int						idx_raw_token;
	int						new_token_start_idx;
	t_chunck				raw_token;
	t_refine_raw_token_vars	*var;
};

void				ft_refined_token_push(
						t_refined_token_push_params params);
void				ft_manage_grouped_and_ungrouped_tokens(
						t_refined_token_push_params scope);
t_chunck			*ft_create_chunck(
						char *token,
						int coord_start,
						int coord_end);
void				ft_refine_raw_token(
						t_chunck raw_token, int curr_idx,
						t_linkedlist_array *container);

#endif
