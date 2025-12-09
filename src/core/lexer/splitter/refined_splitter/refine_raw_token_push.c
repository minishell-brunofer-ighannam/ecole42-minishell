/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_raw_token_push.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 07:45:01 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:16:19 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refined_splitter_internal.h"

static void	ft_push_ungrouped_token(
				t_refined_token_push_params params);
static void	ft_push_grouped_token_part_with_skipped_quotes(
				t_refined_token_push_params params);
static void	ft_push_grouped_token_part(
				t_refined_token_push_params params);

/**
 * # ft_refined_token_push
 *
 * Decides how to insert the refined token
 * into the list:
 * - If it's the first push for that index,
 *   creates the token directly from the
 *   original coordinate.
 * - Otherwise, determines the new start
 *   from the last chunk already inserted.
 *
 * Delegates to `ft_push_ungrouped_token`,
 * `ft_push_grouped_token_part`, or
 * `ft_push_grouped_token_part_with_skipped_quotes`.
 */
void	ft_refined_token_push(t_refined_token_push_params params)
{
	t_linkedlist	*list;
	t_chunck		*last_node_content;

	list = params.refineds->list[params.idx_raw_token];
	if (!list->size)
	{
		params.new_token_start_idx = params.raw_token.coord[0];
		ft_push_ungrouped_token(params);
	}
	else
	{
		last_node_content = (t_chunck *)list->last->content;
		params.new_token_start_idx = last_node_content->coord[1] + 1;
		if (params.var->last_start)
			ft_push_grouped_token_part_with_skipped_quotes(params);
		else
			ft_push_grouped_token_part(params);
	}
}

/**
 * # ft_push_ungrouped_token
 *
 * Inserts a token without any grouping,
 * using the full buffer range directly.
 */
static void	ft_push_ungrouped_token(
				t_refined_token_push_params params
)
{
	params.refineds->push(params.refineds, params.idx_raw_token,
		ft_create_chunck(
			params.var->new_token, params.new_token_start_idx,
			params.new_token_start_idx + params.var->token_len - 1
		)
	);
}

/**
 * # ft_push_grouped_token_part_with_skipped_quotes
 *
 * Used when the token contained multiple
 * consecutive quotes that were skipped
 * during parsing.
 *
 * Inserts only the valid slice, starting
 * from `last_start`.
 */
static void	ft_push_grouped_token_part_with_skipped_quotes(
				t_refined_token_push_params params
)
{
	params.refineds->push(params.refineds, params.idx_raw_token,
		ft_create_chunck(
			params.var->new_token, params.var->last_start,
			params.var->last_start + ft_strlen(params.var->new_token) - 1
		)
	);
}

/**
 * # ft_push_grouped_token_part
 *
 * General case for normal grouped tokens
 * (e.g., `|grep` or `>file.txt`).
 * Inserts the slice using the start
 * calculated by the caller.
 */
static void	ft_push_grouped_token_part(
				t_refined_token_push_params params
)
{
	params.refineds->push(params.refineds, params.idx_raw_token,
		ft_create_chunck(
			params.var->new_token, params.new_token_start_idx,
			params.new_token_start_idx + ft_strlen(params.var->new_token) - 1
		)
	);
}
