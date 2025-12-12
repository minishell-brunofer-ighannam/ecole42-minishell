/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_raw_manage_grouped_and_ungrouped.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:58:40 by valero            #+#    #+#             */
/*   Updated: 2025/12/12 13:52:36 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refined_splitter_internal.h"

static void	filter_reserved_tokens(
				t_chunck token, int curr_idx, t_linkedlist_array *refineds,
				t_refine_raw_token_vars *refine);
static void	manage_quote_behavior(
				t_chunck token, t_refine_raw_token_vars *refine);
static bool	ft_handle_consecutive_quotes(
				t_chunck token, t_refine_raw_token_vars *refine);

/**
 * # ft_manage_grouped_and_ungrouped_tokens
 *
 * Main loop of the character parser.
 *
 * Rules:
 * - Detects quotes and delegates logic
 *   to `manage_quote_behavior`.
 * - When outside quotes, detects reserved
 *   operators via `filter_reserved_tokens`.
 * - Copies normal characters to the final
 *   buffer.
 *
 * Controls the actual navigation of
 * raw tokens.
 */
void	ft_manage_grouped_and_ungrouped_tokens(
			t_refined_token_push_params scope)
{
	while (scope.raw_token.chunck[++scope.var->idx])
	{
		if (ft_is_quote(scope.raw_token.chunck, scope.var->idx, NULL))
			manage_quote_behavior(scope.raw_token, scope.var);
		else
		{
			while (scope.raw_token.chunck[scope.var->idx]
				&& !scope.var->found_quote
				&& is_reserved_token(scope.raw_token.chunck, scope.var->idx))
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
	if (!scope.refineds->nodes_amount && !scope.var->idx_new_token)
		++scope.var->idx_new_token;
}

/**
 * # ft_jump_useless_quotes
 *
 * Advances the index over consecutive
 * useless quotes. Used when sequences
 * like `""""` appear.
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
 * Implements all quote opening and
 * closing logic:
 * - Detects the start of a group.
 * - Skips redundant quotes.
 * - Updates `found_quote`.
 * - Records the group's starting coordinate.
 * - Copies the corresponding character to
 *   `new_token`.
 *
 * This is the most sensitive part for
 * cases like `"hi""""how are you?"`.
 */
static void	manage_quote_behavior(
				t_chunck token, t_refine_raw_token_vars *refine)
{
	if (ft_handle_consecutive_quotes(token, refine))
		return ;
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

static bool	ft_handle_consecutive_quotes(
				t_chunck token, t_refine_raw_token_vars *refine)
{
	int	quote_end_idx;

	quote_end_idx = refine->idx;
	if (!refine->found_quote
		&& token.chunck[quote_end_idx] != token.chunck[quote_end_idx + 1])
	{
		refine->found_quote = token.chunck[refine->idx];
		refine->new_token[refine->idx_new_token++] = token.chunck[refine->idx];
		return (true);
	}
	if (!refine->found_quote && ft_is_quote(token.chunck, refine->idx, NULL))
		while (ft_is_quote(token.chunck, quote_end_idx, NULL)
			&& ft_is_quote(token.chunck, quote_end_idx + 1, NULL))
			quote_end_idx++;
	if (quote_end_idx != refine->idx
		&& (quote_end_idx - refine->idx + 1) % 2 == 0)
	{
		refine->idx = quote_end_idx;
		return (true);
	}
	return (false);
}

/**
 * # filter_reserved_tokens
 *
 * Identifies reserved operators
 * (`|`, `>>`, `<<`, `>`, `<`, ...).
 *
 * Logic:
 * - Only acts when outside quotes.
 * - If there was text before the operator,
 *   pushes it as a separate token.
 * - Creates a chunk for the operator.
 * - Advances the index by the operator's
 *   width.
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
