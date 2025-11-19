/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_raw_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 01:29:30 by valero            #+#    #+#             */
/*   Updated: 2025/11/19 10:15:06 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

/**
 * # ft_refine_raw_token
 *
 * ---
 *
 * Refines a single raw token by handling quotes and
 * reserved tokens.
 *
 * ## Logic
 * - Allocates a temporary buffer `new_token`.
 * - Iterates characters in `raw_token`.
 * - Handles quotes using `manage_quote_behavior()`.
 * - Detects and separates reserved tokens with
 *   `filter_reserved_tokens()`.
 * - Adds resulting tokens to `refineds`.
 *
 * ## Parameters
 * - `raw_token`: The raw token to refine.
 * - `idx_raw_token`: Index of the token in the raw array.
 * - `refineds`: Linked list array to store output tokens.
 *
 * ## Returns
 * - None (refined tokens stored in `refineds`).
 *
 * ## Notes
 * - Merges adjacent strings split by quotes.
 * - Preserves escaped characters.
 */
void	ft_refine_raw_token(
				t_chunck raw_token,
				int idx_raw_token,
				t_linkedlist_array *refineds)
{
	t_refine_raw_token_vars		var;
	int							new_token_start_idx;
	t_refined_token_push_params	scope;

	new_token_start_idx = 0;
	scope.idx_raw_token = idx_raw_token;
	scope.new_token_start_idx = new_token_start_idx;
	scope.raw_token = raw_token;
	scope.refineds = refineds;
	scope.var = &var;
	ft_bzero(scope.var, sizeof(var));
	scope.var->token_len = raw_token.coord[1] - raw_token.coord[0] + 1;
	scope.var->new_token = ft_calloc(scope.var->token_len + 1, sizeof(char));
	scope.var->idx = -1;
	ft_manage_grouped_and_ungrouped_tokens(scope);
	if (var.idx_new_token > 0)
		ft_refined_token_push(scope);
	free(var.new_token);
}
