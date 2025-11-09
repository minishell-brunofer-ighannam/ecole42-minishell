/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:57:24 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 20:45:47 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

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

/**
 * # ft_is_valid_backslash
 *
 * ---
 *
 * Determines if a backslash at `str[idx]` is valid,
 * meaning it effectively escapes the next character.
 *
 * It counts consecutive backslashes backward from
 * `idx` to decide if the sequence is odd (valid) or
 * even (invalid).
 *
 * ## Logic
 * - Scans backward from `idx` counting `\\`.
 * - Stops when reaching a non-backslash or start.
 * - If no backslashes → false.
 * - Returns true if count is odd.
 *
 * ## Parameters
 * - `str`: Input string to check.
 * - `idx`: Index of suspected backslash.
 *
 * ## Returns
 * - `true` if the backslash escapes the next char.
 * - `false` if it is neutral or part of an even pair.
 *
 * ## Notes
 * - Prevents false positives on `\\\\` sequences.
 * - Used to validate quotes and escaped symbols.
 */
bool	ft_is_valid_backslash(const char *str, int idx)
{
	int	counter;

	if (!idx)
		return (str[idx] == '\\');
	counter = 0;
	while (idx >= 0)
	{
		if (str[idx] == '\\' && idx && str[idx - 1] != '\\')
		{
			counter++;
			break ;
		}
		else if (str[idx] == '\\')
			counter++;
		else
			break ;
		idx--;
	}
	if (!counter)
		return (false);
	return (counter % 2);
}

int	is_reserved_token(char *str, int idx)
{
	if (idx > 0 && ft_is_valid_backslash(str, idx - 1))
		return (0);
	if ((str[idx + 1]
		&& str[idx] == '>'  && ft_strchr("|&>", str[idx + 1]))				// >| >& >>
		|| (str[idx] == '&' && ft_strchr("&>", str[idx + 1]))				// && &>
		|| (str[idx] == '<' && ft_strchr("<>", str[idx + 1]))				// << <>
		|| (str[idx] == '|' && str[idx + 1] == '|')							// ||
		|| (str[idx] == '2' && str[idx + 1] == '>' && str[idx + 2] != '&')	// 2>
		|| (str[idx] == '$' && str[idx + 1] == '(')							// $(
		)
		return (2);
	if (ft_strchr("|()<>;&`", str[idx]))									// | ( ) < > ; &
		return (1);
	return (0);
}
