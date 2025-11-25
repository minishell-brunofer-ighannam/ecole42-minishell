/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_raw_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 01:29:30 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 23:08:10 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refined_splitter_internal.h"

/**
 * # ft_refine_raw_token
 *
 * Coração do refinamento de cada token bruto.
 *
 * Lógica:
 * - Prepara variáveis internas e buffer.
 * - Calcula tamanho real do token pelas coordenadas.
 * - Executa o parser de agrupamentos e aspas via
 *   `ft_manage_grouped_and_ungrouped_tokens`.
 * - Caso tenha sobrado conteúdo pendente em new_token,
 *   empurra com `ft_refined_token_push`.
 *
 * Responsável por aplicar toda a lógica de segmentação fina.
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
