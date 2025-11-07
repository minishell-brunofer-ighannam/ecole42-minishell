/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:57:24 by valero            #+#    #+#             */
/*   Updated: 2025/11/07 00:58:05 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

/**
 * # ft_is_quote
 *
 * ---
 *
 * Checks if the character at a given index in `str`
 * is a valid, non-escaped quote.
 *
 * Used during raw string scanning to detect where
 * quotes open or close quoted segments.
 *
 * ## Logic
 * - If `idx == 0` and the first character is `'` or `"`,
 *   returns **true**.
 * - Otherwise, returns **true** only if:
 *   - The previous char is **not** a backslash (`\`), and
 *   - The current char is `'` or `"`.
 * - In all other cases → returns **false**.
 *
 * ## Parameters
 * - `str`: String being analyzed.
 * - `idx`: Index of the character to check.
 *
 * ## Returns
 * - `true`: If the character is a valid quote.
 * - `false`: Otherwise.
 *
 * ## Notes
 * - Escaped quotes (like `\"`) are ignored.
 * - Prevents false detections caused by escaped characters.
 * - The `idx == 0` check avoids out-of-bounds access.
 */
bool	ft_is_quote(const char *str, int idx)
{
	if (!idx && (str[idx] == '\'' || str[idx] == '"'))
		return (true);
	if (str[idx - 1] != '\\' && (str[idx] == '\'' || str[idx] == '"'))
		return (true);
	return (false);
}
