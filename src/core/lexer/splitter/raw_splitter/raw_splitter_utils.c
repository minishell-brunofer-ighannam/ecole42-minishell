/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_splitter_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:27:34 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:11:21 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raw_splitter_internal.h"

/**
 * # ft_raw_splitter_update_word_start
 *
 * Marks the starting index of a word,
 * but only when the quote state allows
 * it (outside or opening quotes).
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
 * Marks the end of a word.
 * Also handles quote closing and
 * state reset.
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
 * Updates the quote FSM state **before**
 * extracting word coordinates. An auxiliary
 * step that interprets the current character
 * and adjusts `quote_info` according to
 * internal rules for:
 * - entering quotes
 * - consecutive quotes
 * - multiple backtick closings
 * - start/end of a quoted block
 *
 * Essential for the later phase to
 * correctly identify word boundaries
 * inside/outside quoted regions.
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
 * Core of the parser. Scans the string
 * character by character and determines
 * where words start and end.
 *
 * Logic:
 * - Maintains a quote FSM via `t_quote_info`.
 * - Detects:
 *      * word start
 *      * word end
 *      * transitions between quote states
 * - Fills `array` with {start, end} pairs.
 *
 * This is the most complex stage of
 * the system.
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
