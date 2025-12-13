/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_splitter_quote_states.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:46:14 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/13 17:16:18 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raw_splitter_internal.h"

/**
 * # ft_raw_splitter_update_quote_state
 *
 * Updates the state of the quote FSM,
 * deciding if we are opening, inside,
 * closing, or exiting quotes.
 *
 * Logic:
 * - Has two flows: end-of-word and
 *   normal character.
 * - Controls the value of `open_quote_type`.
 */
void	ft_raw_splitter_update_quote_state(t_quote_info *quote_info, char quote,
		bool is_word_end)
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
 * # ft_is_start_quote_after_multiple_closing
 *
 * Detects the specific case where a new
 * quote starts immediately after multiple
 * closings, involving backticks.
 *
 * ---
 *
 * ## Example:
 * `...end""""""""new start"`
 */
bool	ft_is_start_quote_after_multiple_closing(const char *str, int i,
		t_quote_state state)
{
	return (i && ft_is_quote(str, i, "`") && !ft_is_quote(str, i + 1, "`")
		&& ft_is_quote(str, i - 1, "`") && state == CLOSED_QUOTE);
}

/**
 * # ft_has_entered_quote
 *
 * Determines if the parser has just
 * entered the internal content of a quote.
 *
 * ---
 *
 * ## Example:
 * `..."entered a quote...`
 */
bool	ft_has_entered_quote(const char *str, int i, t_quote_state state)
{
	return (!ft_is_quote(str, i, "`") && state == QUOTE_OPEN);
}

/**
 * # ft_is_start_consecutive_quote
 *
 * Detects consecutive quotes (e.g. `''''''`)
 * that change the type of open quote.
 *
 * Useful for unconventional backtick patterns.
 *
 * ---
 *
 * ## Example:
 * `...starting consecutive quotes""""""...`
 */
bool	ft_is_start_consecutive_quote(const char *str, int i,
		t_quote_info quote_info)
{
	return (quote_info.state == INSIDE_QUOTE && ft_is_quote(str, i, "`")
		&& ft_is_quote(str, i + 1, "`")
		&& str[i + 1] != quote_info.open_quote_type);
}

/**
 * # ft_is_start_or_end_quote
 *
 * Checks if the current position marks
 * the start or end of a quoted block,
 * considering the type of open quote.
 *
 * ---
 *
 * ## Example:
 * `...before"start or end of quotes"after...`
 */
bool	ft_is_start_or_end_quote(const char *str, int i,
		t_quote_info quote_info)
{
	return ((!i && ft_is_quote(str, i, "`") && !ft_is_quote(str, i + 1, "`"))
		|| (i && ft_is_quote(str, i, "`") && !ft_is_quote(str, i + 1, "`")
			&& !ft_is_quote(str, i - 1, "`") && (!quote_info.open_quote_type
				|| quote_info.open_quote_type == str[i]))
		|| (i && ft_is_quote(str, i, "`")
			&& !ft_is_quote(str, i + 1, "`") && !quote_info.open_quote_type));
}
