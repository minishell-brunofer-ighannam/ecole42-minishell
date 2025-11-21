/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_raw_token_push.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 07:45:01 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 23:10:51 by valero           ###   ########.fr       */
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
 * Decide como inserir o token refinado dentro da lista:
 * - Se é o primeiro push daquele índice, cria token direto
 *   a partir da coordenada original.
 * - Senão, determina o novo start a partir do último chunk
 *   já inserido.
 *
 * Encaminha para `ft_push_ungrouped_token`,
 * `ft_push_grouped_token_part` ou
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
 * Insere um token que não contém agrupamentos,
 * usando diretamente o intervalo completo do buffer.
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
 * Usado quando o token continha múltiplas aspas consecutivas
 * que foram ignoradas na leitura.
 *
 * Insere apenas o trecho válido, iniciando em last_start.
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
 * Caso geral de tokens agrupados normais (ex: `|grep` ou `>file.txt`).
 * Insere o trecho usando o start calculado pelo caller.
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
