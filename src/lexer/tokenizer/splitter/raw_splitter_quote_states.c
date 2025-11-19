/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_splitter_quote_states.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:46:14 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/19 06:54:03 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

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
void	ft_raw_splitter_update_quote_state(
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

bool	ft_is_start_quote_after_multiple_closing(
			const char *str, int i, t_quote_state state)
{
	return (ft_is_quote(str, i, "`") && !ft_is_quote(str, i + 1, "`")
		&& ft_is_quote(str, i - 1, "`") && state == CLOSED_QUOTE);
}

bool	ft_has_entered_quote(const char *str, int i, t_quote_state state)
{
	return (!ft_is_quote(str, i, "`") && state == QUOTE_OPEN);
}

bool	ft_is_start_consecutive_quote(
			const char *str, int i, t_quote_info quote_info)
{
	return (quote_info.state == INSIDE_QUOTE && ft_is_quote(str, i, "`")
		&& ft_is_quote(str, i + 1, "`")
		&& str[i + 1] != quote_info.open_quote_type);
}

bool	ft_is_start_or_end_quote(
			const char *str, int i, t_quote_info quote_info)
{
	return (ft_is_quote(str, i, "`") && !ft_is_quote(str, i + 1, "`")
		&& !ft_is_quote(str, i - 1, "`") && (!quote_info.open_quote_type
			|| quote_info.open_quote_type == str[i]));
}
