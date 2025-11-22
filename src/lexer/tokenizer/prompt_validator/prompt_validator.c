/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:02:05 by valero            #+#    #+#             */
/*   Updated: 2025/11/21 19:28:52 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

/**
 * # prompt_validator
 *
 * Executa todos os validadores de estruturas aninhadas:
 * - aspas simples
 * - parênteses normais
 * - aspas duplas
 * - `$()` (dollar-parens)
 * - backquotes
 *
 * Retorna:
 * - índice do erro mais “profundo” (menor índice válido)
 * - ou -1 se estiver tudo correto.
 *
 * Lógica:
 * - Executa cada validador separadamente.
 * - Armazena os resultados em `checks`.
 * - Retorna o menor índice com `ft_get_smaller`.
 */
int	prompt_validator(const char *line)
{
	int	error_index;
	int	checks[5];

	error_index = -1;
	error_index = validate_singlequotes(line);
	checks[0] = error_index;
	error_index = validate_parens(line);
	checks[1] = error_index;
	error_index = validate_doublequotes(line);
	checks[2] = error_index;
	error_index = validate_dollar_parens(line);
	checks[3] = error_index;
	error_index = validate_backquotes(line);
	checks[4] = error_index;
	return (ft_get_smaller(5, checks));
}
