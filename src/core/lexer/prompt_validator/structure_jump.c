/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_jump.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:55:01 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/24 22:57:21 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

/**
 * # jump_to_closing
 *
 * Função chave para navegação de estruturas aninhadas.
 * Avança o índice até o caractere de fechamento correto,
 * respeitando o tipo da estrutura (", ', `, (), $()).
 *
 * Lógica:
 * - Determina o caractere de fechamento.
 * - Usa `verify_char` para detectar erros dentro do bloco.
 * - Caso não haja erro interno, pula até `get_end`.
 */
void	jump_to_closing(
	const char *line, int *idx,
	int *inner_openning_idx, int (*validate)(const char *line))
{
	char	structure[2];

	structure[1] = 0;
	if (validate == ft_validate_doublequotes)
		structure[0] = '"';
	if (validate == ft_validate_parens || validate == ft_validate_dollar_parens)
		structure[0] = ')';
	if (validate == ft_validate_backquotes)
		structure[0] = '`';
	if (validate == ft_validate_singlequotes)
		structure[0] = '\'';
	*inner_openning_idx = verify_char(
			ft_char_checker(line, *idx, (char *)structure, ft_is_special_char),
			validate);
	if (*inner_openning_idx > -1)
		*inner_openning_idx = *idx + *inner_openning_idx;
	else
		*idx = get_end(line, *idx, ft_is_special_char, (char *)structure) + 1;
}
