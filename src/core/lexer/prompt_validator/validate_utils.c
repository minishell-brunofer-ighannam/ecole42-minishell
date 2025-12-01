/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:48:52 by valero            #+#    #+#             */
/*   Updated: 2025/11/29 20:46:35 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

/**
 * # verify_char
 *
 * Extrai um trecho da string que representa uma estrutura
 * delimitada e o envia para o validador apropriado.
 *
 * Lógica:
 * - Cria substring usando `get_end` como limite.
 * - Executa o validador nessa substring.
 * - Se o validador localizar erro, retorna o índice relativo.
 */
int	verify_char(t_char_checker checker, int (*verify)(const char *line))
{
	char	*sub;
	int		openning_idx;

	sub = ft_substr(checker.str, checker.idx,
			get_end(checker.str, checker.idx,
				checker.is_special_char, checker.chars) + 1 - checker.idx);
	openning_idx = verify(sub);
	free(sub);
	if (openning_idx > -1)
		return (openning_idx);
	return (-1);
}

/**
 * # ft_char_checker
 *
 * Inicializa um `t_char_checker` com os dados necessários
 * para validação de estruturas internas.
 */
t_char_checker	ft_char_checker(const char *str, int idx, char *chars,
					bool (*is_special_char)(
						const char *str, int idx, char *chars))
{
	t_char_checker	checker;

	checker.str = str;
	checker.idx = idx;
	checker.chars = chars;
	checker.is_special_char = is_special_char;
	return (checker);
}

/**
 * # ft_get_smaller
 *
 * Dado um array de índices, retorna o menor índice válido
 * (>= 0). Se todos forem inválidos, retorna -1.
 *
 * Usado para decidir qual erro tem prioridade.
 */
int	ft_get_smaller(int len, int *arr)
{
	int	smaller;

	smaller = INT_MAX;
	while (--len >= 0)
		if (arr[len] >= 0 && arr[len] < smaller)
			smaller = arr[len];
	if (smaller == INT_MAX)
		return (-1);
	return (smaller);
}

/**
 * # fill_int_array
 *
 * Inicializa um array de inteiros com um único valor.
 * Utilidade simples para preparação de arrays de índices.
 */
void	fill_int_array(int *array, int len, int value)
{
	while (--len >= 0)
		array[len] = value;
}
