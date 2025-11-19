/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_raw_token_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 07:45:01 by valero            #+#    #+#             */
/*   Updated: 2025/11/19 09:40:47 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

static void	ft_push_ungrouped_token(
				t_refined_token_push_params params);
static void	ft_push_grouped_token_part_with_skipped_quotes(
				t_refined_token_push_params params);
static void	ft_push_grouped_token_part(
				t_refined_token_push_params params);

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

// em caso de token agrupado com múltiplas áspas`"ola """"tudo bem?"`
// onde as áspas "inúteis" foram puladas
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

// em caso de token agrupado com nada pulado `|grep` ou `>file.txt`
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
