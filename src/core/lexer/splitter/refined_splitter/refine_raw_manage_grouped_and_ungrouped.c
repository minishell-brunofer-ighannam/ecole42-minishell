/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_raw_manage_grouped_and_ungrouped.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:58:40 by valero            #+#    #+#             */
/*   Updated: 2025/11/26 19:48:30 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refined_splitter_internal.h"

static void	filter_reserved_tokens(
				t_chunck token, int curr_idx, t_linkedlist_array *refineds,
				t_refine_raw_token_vars *refine);
static void	manage_quote_behavior(
				t_chunck token, t_refine_raw_token_vars *refine);

/**
 * # ft_manage_grouped_and_ungrouped_tokens
 *
 * Loop principal do parser de caracteres.
 *
 * Regras:
 * - Detecta aspas e delega a lógica para `manage_quote_behavior`.
 * - Quando não está dentro de aspas, detecta operadores reservados
 *   via `filter_reserved_tokens`.
 * - Copia caracteres normais para o buffer final.
 *
 * É quem controla a navegação real no token bruto.
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
}

/**
 * # ft_jump_useless_quotes
 *
 * Avança o índice por cima de aspas consecutivas inúteis.
 * Usado quando sequências como `""""` aparecem.
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
 * Implementa toda a lógica de abertura e fechamento de aspas:
 * - Detecta início de um agrupamento.
 * - Pula aspas redundantes.
 * - Atualiza found_quote.
 * - Registra coordenada inicial do grupo.
 * - Copia o caractere correspondente para new_token.
 *
 * É a parte mais sensível para casos como:
 * `"oi""""tudo bem?"`.
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
 * Identifica operadores reservados (`|`, `>`>, `<<`, `>`, `<`, ...).
 *
 * Lógica:
 * - Só atua quando não estamos dentro de aspas.
 * - Se havia texto acumulado antes do operador,
 *   empurra-o como um token separado.
 * - Cria um chunk para o operador.
 * - Avança o índice pela largura do operador.
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
