/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_backquotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:56:18 by valero            #+#    #+#             */
/*   Updated: 2025/11/21 14:57:36 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

static void	jump_inner_structures(
				const char *line, int *idx, int *inner_openning_idx);
static void	update_open_index(int *open_idx, int curr_idx);

/**
 * # validate_backquotes
 *
 * Verifica se os backquotes estão corretamente abertos e fechados.
 * Também detecta estruturas internas que possam causar erro.
 *
 * Lógica:
 * - Percorre o texto alternando entre estados “aberto/fechado”.
 * - Se encontrar estruturas internas, delega a `jump_inner_structures`.
 * - Retorna índice do erro ou -1 se válido.
 */
int	validate_backquotes(const char *line)
{
	int		i;
	int		open_backquotes_index;
	int		other_openning_idx[4];

	fill_int_array(other_openning_idx, 4, -1);
	open_backquotes_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_backquotes_index > -1)
			jump_inner_structures(line, &i, other_openning_idx);
		if (!line[i])
			break ;
		if (ft_is_special_char(line, i, "`"))
			update_open_index(&open_backquotes_index, i);
	}
	if (open_backquotes_index == -1)
		return (ft_get_smaller(3, other_openning_idx));
	return (open_backquotes_index);
}

/**
 * # jump_inner_structures (variações internas)
 *
 * Avança por estruturas internas quando já se está dentro
 * de outra estrutura. Evita falsos positivos.
 *
 * Tipos que podem ser pulados:
 * - aspas duplas
 * - aspas simples
 * - parênteses
 * - backquotes
 * - `$()`
 */
static void	jump_inner_structures(
				const char *line, int *idx, int *inner_openning_idx)
{
	if (ft_is_special_char(line, *idx, "\""))
		jump_to_closing(
			line, idx, inner_openning_idx + 0, validate_doublequotes);
	if (ft_is_special_char(line, *idx, "'"))
		jump_to_closing(
			line, idx, inner_openning_idx + 1, validate_singlequotes);
	else if (ft_is_special_char(line, *idx, "()"))
		jump_to_closing(line, idx, inner_openning_idx + 2, validate_parens);
	else if (ft_is_special_char(line, *idx, "$") && line[*idx + 1] == '(')
		jump_to_closing(
			line, idx, inner_openning_idx + 3, validate_dollar_parens);
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
