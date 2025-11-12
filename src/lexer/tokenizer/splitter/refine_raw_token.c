/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_raw_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 01:29:30 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 22:44:20 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

static void	ft_jump_useless_quotes(char *str, int *curr_idx);
static void	filter_reserved_tokens(
				char *token, int curr_idx, t_linkedlist_array *refineds,
				t_refine_raw_token_vars *refine);
static void	manage_quote_behavior(
				char *token, t_refine_raw_token_vars *refine);

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
				char *raw_token,
				int idx_raw_token,
				t_linkedlist_array *refineds)
{
	t_refine_raw_token_vars	var;

	var.token_len = ft_strlen(raw_token);
	var.new_token = ft_calloc(var.token_len + 1, sizeof(char));
	var.idx_new_token = 0;
	var.found_quote = 0;
	var.idx = -1;
	while (raw_token[++var.idx])
	{
		if (ft_is_quote(raw_token, var.idx, NULL))
			manage_quote_behavior(raw_token, &var);
		else
		{
			filter_reserved_tokens(raw_token, idx_raw_token, refineds, &var);
			if (raw_token[var.idx])
				var.new_token[var.idx_new_token++] = raw_token[var.idx];
			else
				break ;
		}
	}
	if (var.idx_new_token > 0)
		refineds->push(refineds, idx_raw_token, ft_strdup(var.new_token));
	free(var.new_token);
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
 * # ft_merge_adjacent_strings
 *
 * ---
 *
 * Decides whether a quote character should be appended
 * to the current refined token.
 *
 * ## Logic
 * - Checks token position and surrounding characters.
 * - Appends quote if it bridges adjacent strings.
 *
 * ## Parameters
 * - `token`: The current raw token.
 * - `refine`: Refinement state struct (`t_refine_raw_token_vars`).
 *
 * ## Returns
 * - None (modifies `refine->new_token`).
 *
 * ## Notes
 * - Prevents accidental token splitting at quotes.
 */
static void	ft_merge_adjacent_strings(
				char *token, t_refine_raw_token_vars *refine)
{
	int		idx;
	char	*new_token;
	int		*idx_new_token;

	idx = refine->idx;
	new_token = refine->new_token;
	idx_new_token = &refine->idx_new_token;
	if (!idx && token[idx + 1]
		&& ft_is_quote(token, idx, NULL) && !ft_is_quote(token, idx + 1, NULL))
		new_token[(*idx_new_token)++] = token[idx];
	else if (token[idx] && !token[idx + 1] && token[idx - 1]
		&& ft_is_quote(token, idx, NULL) && !ft_is_quote(token, idx - 1, NULL))
		new_token[(*idx_new_token)++] = token[idx];
	else if (token[idx] && token[idx + 1] && token[idx - 1]
		&& ft_is_quote(token, idx, NULL) && !ft_is_quote(token, idx + 1, NULL)
		&& ft_is_quote(token, idx, NULL) && !ft_is_quote(token, idx - 1, NULL))
		new_token[(*idx_new_token)++] = token[idx];
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
				char *token, int curr_idx, t_linkedlist_array *refineds,
				t_refine_raw_token_vars *refine)
{
	if (!refine->found_quote && is_reserved_token(token, refine->idx))
	{
		if (refine->idx_new_token > 0)
			refineds->push(refineds, curr_idx,
				ft_strdup(refine->new_token));
		refine->idx_new_token = 0;
		ft_bzero(refine->new_token, refine->token_len * sizeof(char));
		refineds->push(refineds, curr_idx,
			ft_substr(token,
				refine->idx,
				is_reserved_token(token, refine->idx)));
		refine->idx += is_reserved_token(token, refine->idx);
	}
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
				char *token, t_refine_raw_token_vars *refine)
{
	if (refine->idx > 0 && !refine->found_quote)
	{
		refine->found_quote = token[refine->idx];
		ft_jump_useless_quotes(token + refine->idx, &refine->idx);
	}
	else if (!refine->found_quote)
		refine->found_quote = token[refine->idx];
	else if (refine->found_quote == token[refine->idx])
		refine->found_quote = 0;
	ft_merge_adjacent_strings(token, refine);
}
