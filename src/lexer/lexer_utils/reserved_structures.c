/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserved_structures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:20:34 by valero            #+#    #+#             */
/*   Updated: 2025/11/22 17:54:21 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils_internal.h"

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
	if (str[idx + 1]
		&& ((str[idx] == '>'  && ft_strchr("|&>", str[idx + 1]))				// >| >& >>
		|| (str[idx] == '&' && ft_strchr("&>", str[idx + 1]))				// && &>
		|| (str[idx] == '<' && ft_strchr("<>", str[idx + 1]))				// << <>
		|| (str[idx] == '|' && str[idx + 1] == '|')							// ||
		|| (str[idx] == '2' && str[idx + 1] == '>' && str[idx + 2] != '&')	// 2>
		|| (str[idx] == '$' && str[idx + 1] == '('))							// $(
		)
		return (2);
	if (ft_strchr("|()<>;&`", str[idx]))									// | ( ) < > ; &
		return (1);
	return (0);
}

bool	ft_is_special_char(const char *str, int idx, char *chars)
{
	bool	is_chars;

	if (!str[idx])
		return (false);
	is_chars = ft_strchr(chars, str[idx]);
	if (!idx && (is_chars))
		return (true);
	if (!ft_is_valid_backslash(str, idx - 1) && (is_chars))
		return (true);
	return (false);
}
