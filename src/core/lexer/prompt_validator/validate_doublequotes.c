/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_doublequotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:10:54 by valero            #+#    #+#             */
/*   Updated: 2025/12/08 15:10:56 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

static void	jump_inner_structures(
				const char *line, int *idx,
				int *inner_openning_idx, int open_in_main);
static void	update_open_index(int *open_idx, int curr_idx);

/**
 * # ft_validate_doublequotes
 *
 * Valida aspas duplas, incluindo estruturas internas.
 * Aspas duplas permitem interpretar conteúdo, portanto
 * exigem navegação de estruturas aninhadas.
 */
int	ft_validate_doublequotes(const char *line)
{
	int	i;
	int	open_quote_index;
	int	other_openning_idx[2];

	fill_int_array(other_openning_idx, 2, -1);
	open_quote_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_quote_index == -1 && ft_is_special_char(line, i, "'"))
			i = get_end(line, i, ft_is_special_char, "'") + 1;
		if (open_quote_index > -1)
			jump_inner_structures(
				line, &i, other_openning_idx, open_quote_index);
		if (!line[i])
			break ;
		if (ft_is_special_char(line, i, "\""))
			update_open_index(&open_quote_index, i);
	}
	if (open_quote_index == -1)
		return (ft_get_smaller(2, other_openning_idx));
	return (open_quote_index);
}

/**
 * # jump_inner_structures (variações internas)
 *
 * Avança por estruturas internas quando já se está dentro
 * de outra estrutura. Evita falsos positivos.
 *
 * Tipos que podem ser pulados:
 * - backquotes
 * - `$()`
 */
static void	jump_inner_structures(
			const char *line, int *idx,
			int *inner_openning_idx, int open_in_main)
{
	if (ft_is_special_char(line, *idx, "`"))
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				inner_openning_idx + 0, ft_validate_backquotes),
			open_in_main);
	else if (ft_is_special_char(line, *idx, "$") && line[*idx + 1] == '(')
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				inner_openning_idx + 1, ft_validate_dollar_parens),
			open_in_main);
}

/**
 * # update_open_index (versão simples)
 *
 * Alterna estado de abertura/fechamento de estruturas simples
 * como aspas ou backquotes.
 */
static void	update_open_index(int *open_idx, int curr_idx)
{
	if (*open_idx == -1)
		*open_idx = curr_idx;
	else
		*open_idx = -1;
}
