/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_jump.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:55:01 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/07 13:17:31 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

static char	ft_get_corresponding_closing(const char *str);

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
	int *inner_openning_idx, int (*validate)(const char *line),
	int open_in_main)
{
	char	structure[2];
	int		tmp;
	bool	is_dollar_parens;
	char	start_corresp_closing;

	start_corresp_closing = ft_get_corresponding_closing(line + open_in_main);
	is_dollar_parens = validate == ft_validate_dollar_parens;
	structure[1] = 0;
	if (validate == ft_validate_doublequotes)
		structure[0] = '"';
	if (validate == ft_validate_parens || is_dollar_parens)
		structure[0] = ')';
	if (validate == ft_validate_backquotes)
		structure[0] = '`';
	if (validate == ft_validate_singlequotes)
		structure[0] = '\'';
	*inner_openning_idx = verify_char(
			ft_char_checker(line, *idx, (char *)structure, ft_is_special_char),
			validate);
	if (*inner_openning_idx > -1)
	{
		tmp = *inner_openning_idx;
		if (is_dollar_parens)
			tmp--;
		if (*inner_openning_idx && line[*inner_openning_idx + *idx] == start_corresp_closing)
			*inner_openning_idx = open_in_main + *inner_openning_idx + (int)is_dollar_parens;
		else
			*inner_openning_idx = *idx + *inner_openning_idx;
		if (tmp + *idx > *idx)
		{
			structure[0] = start_corresp_closing;
			*idx = get_end(line, open_in_main, ft_is_special_char, (char *)structure) - 1;
		}
		// if (line[*idx + 1] == structure[0])
		// 	(*idx)++;
	}
	else
		*idx = get_end(line, *idx, ft_is_special_char, (char *)structure) + 1;
}

void	jump_quotes(const char *line, int *idx)
{
	if (ft_is_special_char(line, *idx, "\""))
		*idx = get_end(line, *idx, ft_is_special_char, "\"") + 1;
	if (ft_is_special_char(line, *idx, "'"))
		*idx = get_end(line, *idx, ft_is_special_char, "'") + 1;
}

static char	ft_get_corresponding_closing(const char *str)
{
	if (str[0] == '\"')
		return ('"');
	if (str[0] == '\'')
		return ('\'');
	if (str[0] == '`')
		return ('`');
	if (str[0] == '(')
		return (')');
	if (str[0] == '$' && str[1] == '(')
		return (')');
	return (0);
}
