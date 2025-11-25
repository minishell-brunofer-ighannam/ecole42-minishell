/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_splitter_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:27:34 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 22:11:51 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raw_splitter_internal.h"

/**
 * # ft_raw_splitter_update_word_start
 *
 * Marca o índice inicial de uma palavra,
 * mas apenas quando o estado de aspas permite
 * (fora ou abrindo aspas).
 */
static void	ft_raw_splitter_update_word_start(
		t_quote_info *quote_info, t_int_array *array, int idx)
{
	if (quote_info->state == NO_QUOTE_OPEN || quote_info->state == QUOTE_OPEN)
		array->array[array->len++] = idx;
}

/**
 * # ft_raw_splitter_update_word_end
 *
 * Marca o encerramento de uma palavra.
 * Também lida com fechamento de aspas e
 * reinicialização do estado.
 */
static void	ft_raw_splitter_update_word_end(
		t_quote_info *quote_info, t_int_array *array, int idx)
{
	if (quote_info->state == NO_QUOTE_OPEN || quote_info->state == CLOSED_QUOTE)
	{
		array->array[array->len++] = idx - 1;
		if (quote_info->state == CLOSED_QUOTE)
		{
			ft_raw_splitter_update_quote_state(quote_info, '"', true);
			quote_info->open_quote_type = 0;
		}
	}
}

/**
 * # ft_quote_fsm_before_coord_extraction
 *
 * Atualiza o estado da FSM de aspas **antes** da extração
 * de coordenadas de palavras. É uma etapa auxiliar que
 * interpreta o caractere atual e ajusta `quote_info`
 * conforme regras internas de:
 * - entrada em aspas
 * - aspas consecutivas
 * - múltiplos fechamentos com backticks
 * - início/fim de bloco de aspas
 *
 * Essencial para que a fase posterior identifique corretamente
 * início/fim de palavras levando em conta regiões entre aspas.
 *
 */
static void	ft_quote_fsm_before_coord_extraction(
				const char *str, int i, t_quote_info *quote_info)
{
	if (ft_has_entered_quote(str, i, quote_info->state))
		quote_info->state = INSIDE_QUOTE;
	if (ft_is_start_consecutive_quote(str, i, *quote_info))
		quote_info->open_quote_type = str[i + 1];
	if (ft_is_start_quote_after_multiple_closing(str, i, quote_info->state))
		ft_raw_splitter_update_quote_state(quote_info, str[i], false);
	if (ft_is_start_or_end_quote(str, i, *quote_info))
		ft_raw_splitter_update_quote_state(quote_info, str[i], false);
}

/**
 * # ft_raw_splitter_get_words_position
 *
 * Núcleo do parser. Varre o string caractere por caractere
 * e determina onde palavras começam e terminam.
 *
 * Lógica:
 * - Mantém uma FSM (Finite State Machine) de aspas via `t_quote_info`.
 * - Detecta:
 *      * início de palavra
 *      * fim de palavra
 *      * transições entre estados de aspas
 * - Preenche `array` com pares {start, end}.
 *
 * É a etapa mais complexa do sistema.
 */
void	ft_raw_splitter_get_words_position(
			const char *str, t_int_array *array)
{
	int				i;
	t_quote_info	quote_info;

	ft_bzero(&quote_info, sizeof(t_quote_info));
	quote_info.state = NO_QUOTE_OPEN;
	i = -1;
	while (str[++i])
	{
		ft_quote_fsm_before_coord_extraction(str, i, &quote_info);
		if (((i == 0) && (str[i] != ' '))
			|| ((i > 0) && (str[i] != ' ') && (str[i - 1] == ' ')))
			ft_raw_splitter_update_word_start(&quote_info, array, i);
		else if ((i > 0) && (str[i] == ' ' && str[i - 1] != ' '))
			ft_raw_splitter_update_word_end(&quote_info, array, i);
		else if ((str[i] != ' ' && str[i + 1] == '\0'))
			array->array[array->len++] = i;
	}
	if (array->len % 2 != 0)
		array->array[array->len++] = i - 1;
}
