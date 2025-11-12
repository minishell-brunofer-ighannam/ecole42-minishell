/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:57:24 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 22:44:00 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

/**
 * # ft_is_quote
 *
 * ---
 *
 * Checks if the character at `str[idx]` is a valid
 * quote (`'` or `"`) considering escape rules.
 *
 * A quote is valid if:
 * - It appears at the beginning of the string, or
 * - It is not preceded by a valid backslash.
 *
 * ## Logic
 * - If index is 0 and character is a quote → true.
 * - Otherwise, calls `ft_is_valid_backslash()` to
 *   check if the quote was escaped.
 * - Returns true only if not escaped.
 *
 * ## Parameters
 * - `str`: Input string to inspect.
 * - `idx`: Current index to check.
 *
 * ## Returns
 * - `true` if position contains a valid quote.
 * - `false` otherwise.
 *
 * ## Notes
 * - Handles both single and double quotes.
 * - Integrates with the raw splitter quote logic.
 */
bool	ft_is_quote(const char *str, int idx, char *other_symbols)
{
	bool	is_quote;

	is_quote = str[idx] == '\'' || str[idx] == '"';
	if (other_symbols)
		is_quote = is_quote || ft_strchr(other_symbols, str[idx]);
	if (!idx && (is_quote))
		return (true);
	if (!ft_is_valid_backslash(str, idx - 1) && (is_quote))
		return (true);
	return (false);
}
