/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_splitter_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:27:34 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 20:16:39 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

/**
 * # ft_raw_splitter_update_quote_state
 *
 * ---
 *
 * Updates the quote parsing state within the given
 * `t_quote_info` structure.
 *
 * Each invocation transitions the state machine to
 * the next logical phase of quote handling.
 *
 * ## Logic
 * - `NO_QUOTE_OPEN` → `QUOTE_OPEN`
 * - `QUOTE_OPEN` → `INSIDE_QUOTE`
 * - `INSIDE_QUOTE` → `CLOSED_QUOTE`
 * - `CLOSED_QUOTE` → `NO_QUOTE_OPEN`
 *
 * ## Parameters
 * - `quote_info`: Pointer to quote tracking data.
 *
 * ## Notes
 * - Called whenever a quote character is detected.
 * - Keeps track of quote depth and closure.
 * - `open_quote_type` remains unchanged here;
 *   it should be set elsewhere when a quote opens.
 */
static void	ft_raw_splitter_update_quote_state(
				t_quote_info *quote_info, char quote, bool is_word_end)
{
	if (is_word_end)
	{
		if (quote_info->state == NO_QUOTE_OPEN)
			quote_info->state = QUOTE_OPEN;
		else if (quote_info->state == QUOTE_OPEN)
			quote_info->state = INSIDE_QUOTE;
		else if (quote_info->state == INSIDE_QUOTE)
			quote_info->state = CLOSED_QUOTE;
		else
			quote_info->state = NO_QUOTE_OPEN;
		if (quote_info->state == QUOTE_OPEN)
			quote_info->open_quote_type = quote;
		return ;
	}
	if (quote_info->state == NO_QUOTE_OPEN)
		quote_info->state = QUOTE_OPEN;
	else if (quote_info->state == QUOTE_OPEN)
		quote_info->state = INSIDE_QUOTE;
	else if (quote_info->state == INSIDE_QUOTE)
		quote_info->state = CLOSED_QUOTE;
	else
		quote_info->state = INSIDE_QUOTE;
	if (quote_info->state == QUOTE_OPEN)
			quote_info->open_quote_type = quote;
}

/**
 * # ft_raw_splitter_update_word_start
 *
 * ---
 *
 * Marks the start index of a new word while scanning the raw input.
 *
 * Used by the raw splitter to record the beginning of each
 * word segment in `coord_arr`, respecting quote states.
 *
 * ## Logic
 * - If `quote_state` is `NO_QUOTE_OPEN` or `QUOTE_OPEN`,
 *   record the current index `idx` as a word start.
 * - If `quote_state` is `QUOTE_OPEN` (value 1),
 *   advance the quote state using
 *   `ft_raw_splitter_update_quote_state()`.
 *
 * ## Parameters
 * - `quote_state`: Current quote parsing state.
 * - `coord_arr`: Array that stores start/end indexes.
 * - `coord_arr_len`: Current number of stored indexes.
 * - `idx`: Current character index in the string.
 *
 * ## Notes
 * - Called when a new word begins (non-space after space).
 * - Quotes are respected to avoid splitting quoted text.
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
 * ---
 *
 * Marks the end index of a word segment during raw scanning.
 *
 * Works together with `ft_raw_splitter_update_word_start()`
 * to define the full range of each word.
 *
 * ## Logic
 * - If `quote_state` is `NO_QUOTE_OPEN` or `CLOSED_QUOTE`,
 *   record `idx - 1` as the word end.
 * - If `quote_state` is `CLOSED_QUOTE` (value 3),
 *   call `ft_raw_splitter_update_quote_state()`
 *   to reset to normal parsing.
 *
 * ## Parameters
 * - `quote_state`: Current quote parsing state.
 * - `coord_arr`: Array storing start/end indexes.
 * - `coord_arr_len`: Current number of stored indexes.
 * - `idx`: Current character index in the string.
 *
 * ## Notes
 * - Called when a space or quote ends a word.
 * - Ensures quoted sections close properly.
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
 * # ft_raw_splitter_get_words_position
 *
 * ---
 *
 * Scans a raw string and records the start and end
 * positions of each word or quoted segment.
 *
 * This builds coordinate data for later tokenization,
 * ensuring that quoted words remain intact even if
 * they contain spaces.
 *
 * ## Logic
 * - Loops through each character in `str`.
 * - Updates `quote_state` when a quote is found.
 * - #### Detects **word start** when:
 *   - `i == 0` and not a space, or
 *   - Current char is not space, but previous is.
 *   → Calls `ft_update_word_start()`.
 * - #### Detects **word end** when:
 *   - Current char is space and previous is not.
 *   → Calls `ft_update_word_end()`.
 * - If the string ends with a non-space,
 *   records the last index as a word end.
 * - If coordinates are odd at the end,
 *   closes the last word by appending `i - 1`.
 *
 * ## Parameters
 * - `str`: String to analyze.
 * - `coord_arr`: Array of word start/end indexes.
 * - `coord_arr_len`: Counter of stored indexes.
 *
 * ## Notes
 * - Each word generates two entries: start and end.
 * - Quoted segments are treated as one word.
 * - Does not modify or allocate memory for `str`.
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
		if (!ft_is_quote(str, i, "`") && quote_info.state == QUOTE_OPEN)
			quote_info.state = INSIDE_QUOTE;
		if (ft_is_quote(str, i, "`") && !ft_is_quote(str, i + 1, "`")
			&& !ft_is_quote(str, i - 1, "`") && (!quote_info.open_quote_type
				|| quote_info.open_quote_type == str[i]))
			ft_raw_splitter_update_quote_state(&quote_info, str[i], false);
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
