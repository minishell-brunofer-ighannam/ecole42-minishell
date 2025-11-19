/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_raw_manage_grouped_and_ungrouped.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:58:40 by valero            #+#    #+#             */
/*   Updated: 2025/11/19 10:08:20 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

static void	filter_reserved_tokens(
				t_chunck token, int curr_idx, t_linkedlist_array *refineds,
				t_refine_raw_token_vars *refine);
static void	manage_quote_behavior(
				t_chunck token, t_refine_raw_token_vars *refine);

void	ft_manage_grouped_and_ungrouped_tokens(
			t_refined_token_push_params scope)
{
	while (scope.raw_token.chunck[++scope.var->idx])
	{
		if (ft_is_quote(scope.raw_token.chunck, scope.var->idx, NULL))
			manage_quote_behavior(scope.raw_token, scope.var);
		else
		{
			filter_reserved_tokens(scope.raw_token, scope.idx_raw_token,
				scope.refineds, scope.var);
			if (scope.raw_token.chunck[scope.var->idx])
			{
				if (ft_is_quote(scope.raw_token.chunck, scope.var->idx, NULL))
					manage_quote_behavior(scope.raw_token, scope.var);
				else
					scope.var->new_token[scope.var->idx_new_token++]
						= scope.raw_token.chunck[scope.var->idx];
			}
			else
				break ;
		}
	}
}

/**
 * # ft_jump_useless_quotes
 *
 * ---
 *
 * Skips consecutive quote characters that are not part
 * of a meaningful string.
 *
 * ## Logic
 * - Iterates while characters are quotes.
 * - Increments `curr_idx` to skip them.
 *
 * ## Parameters
 * - `str`: Pointer to token substring starting at quote.
 * - `curr_idx`: Pointer to current index, updated.
 *
 * ## Returns
 * - None (index adjusted in place).
 *
 * ## Notes
 * - Used internally by `manage_quote_behavior()`.
 */
static void	ft_jump_useless_quotes(char *str, int *curr_idx)
{
	int	idx;

	idx = 0;
	while (str[idx] && ft_is_quote(str, idx, NULL))
		idx++;
	*curr_idx += idx - 1;
}

/**
 * # manage_quote_behavior
 *
 * ---
 *
 * Updates the quote state when a quote character is
 * encountered in a token.
 *
 * ## Logic
 * - Sets `found_quote` on opening quote.
 * - Resets `found_quote` on closing quote.
 * - Calls `ft_merge_adjacent_strings()` for special cases.
 *
 * ## Parameters
 * - `token`: The token being refined.
 * - `refine`: Refinement state struct (`t_refine_raw_token_vars`).
 *
 * ## Returns
 * - None (modifies `refine->found_quote` and `new_token`).
 *
 * ## Notes
 * - Ensures quoted segments are preserved correctly.
 */
static void	manage_quote_behavior(
				t_chunck token, t_refine_raw_token_vars *refine)
{
	if (refine->idx > 0 && !refine->found_quote)
	{
		refine->found_quote = token.chunck[refine->idx];
		ft_jump_useless_quotes(token.chunck + refine->idx, &refine->idx);
	}
	else if (!refine->found_quote)
		refine->found_quote = token.chunck[refine->idx];
	else if (refine->found_quote == token.chunck[refine->idx])
		refine->found_quote = 0;

	if (!refine->idx_new_token)
		refine->last_start = token.coord[0] + refine->idx;
	refine->new_token[refine->idx_new_token++] = token.chunck[refine->idx];
}



/**
 * # filter_reserved_tokens
 *
 * ---
 *
 * Detects reserved tokens (like `>`, `|`, `&&`) and
 * separates them from the current token.
 *
 * ## Logic
 * - Checks if the current character is a reserved token.
 * - Pushes accumulated string before reserved token.
 * - Pushes reserved token as a separate element.
 *
 * ## Parameters
 * - `token`: The raw token being processed.
 * - `curr_idx`: Index of the raw token in the array.
 * - `refineds`: Linked list array for output.
 * - `refine`: Refinement state struct.
 *
 * ## Returns
 * - None (modifies `refineds` and `refine` state).
 *
 * ## Notes
 * - Only applies outside of quotes.
 */
static void	filter_reserved_tokens(
				t_chunck token, int curr_idx, t_linkedlist_array *refineds,
				t_refine_raw_token_vars *refine)
{
	char	*reserved;
	int		reserved_len;

	reserved_len = is_reserved_token(token.chunck, refine->idx);
	if (!refine->found_quote && reserved_len)
	{
		if (refine->idx_new_token > 0)
			refineds->push(refineds, curr_idx,
				ft_create_chunck(
					refine->new_token,
					token.coord[0] + refine->idx - refine->idx_new_token,
					token.coord[0] + refine->idx - 1));
		refine->idx_new_token = 0;
		ft_bzero(refine->new_token, refine->token_len * sizeof(char));
		reserved = ft_substr(token.chunck, refine->idx, reserved_len);
		refineds->push(refineds, curr_idx,
			ft_create_chunck(
				reserved,
				token.coord[0] + refine->idx,
				token.coord[0] + refine->idx + reserved_len - 1));
		free(reserved);
		refine->idx += reserved_len;
	}
}
