/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils_get_end.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:55:11 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 17:57:23 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

/**
 * # get_end
 *
 * Finds the closing position of a structure:
 * quotes, backquotes, parentheses, or `$()`.
 *
 * Logic:
 * - Advances to the next matching special
 *   character.
 * - Returns the final position of the block.
 */
int	get_end(const char *str, int idx,
			bool (*is_special_char)(const char *str, int idx, char *chars),
			char *chars)
{
	int		i;

	if (ft_is_dollar_parens(str, idx, is_special_char))
		return (get_end_dollar_parens(str, idx, is_special_char, ")"));
	if (ft_is_parens(str, idx, is_special_char))
		return (get_end_parens(str, idx, is_special_char, ")"));
	if (is_special_char(str, idx, "`"))
		return (get_end_backquotes(str, idx, is_special_char, "`"));
	if (is_special_char(str, idx, "\""))
		return (get_end_doublequotes(str, idx, is_special_char, "\""));
	i = idx;
	while (str[++i])
	{
		if (is_special_char(str, i, chars))
		{
			if (str[i] == chars[0])
				return (i);
		}
	}
	return (i);
}

/**
 * # get_end_parens
 *
 * Finds the closing position of a structure:
 * parentheses `(`.
 *
 * Logic:
 * - Advances to the next matching special
 *   character.
 * - Returns the final position of the block.
 */
int	get_end_parens(const char *str, int idx,
			bool (*is_special_char)(const char *str, int idx, char *chars),
			char *chars)
{
	int	i;
	int	opened_times;

	opened_times = 0;
	i = idx;
	while (str[++i])
	{
		if (ft_is_parens(str, i, is_special_char))
			opened_times++;
		ft_skip_inner_of_parens(str, &i, idx, is_special_char);
		if (!str[i - 1] || !str[i])
			return (idx + 1);
		if (is_special_char(str, i, chars))
		{
			if (str[i] == chars[0])
			{
				if (opened_times)
					opened_times--;
				else
					return (i);
			}
		}
	}
	return (i);
}

/**
 * # get_end_dollar_parens
 *
 * Finds the closing position of a structure:
 * `$(`.
 *
 * Logic:
 * - Advances to the next matching special
 *   character.
 * - Returns the final position of the block.
 */
int	get_end_dollar_parens(const char *str, int idx,
			bool (*is_special_char)(const char *str, int idx, char *chars),
			char *chars)
{
	int	i;
	int	opened_times;

	opened_times = 0;
	i = idx;
	while (str[++i])
	{
		if (ft_is_dollar_parens(str, i, is_special_char))
			opened_times++;
		ft_skip_inner_of_dollar_parens(str, &i, idx, is_special_char);
		if (!str[i - 1] || !str[i])
			return (idx + 1);
		if (is_special_char(str, i, chars))
		{
			if (str[i] == chars[0])
			{
				if (opened_times)
					opened_times--;
				else
					return (i);
			}
		}
	}
	return (i);
}

int	get_end_backquotes(const char *str, int idx,
			bool (*is_special_char)(const char *str, int idx, char *chars),
			char *chars)
{
	int		i;

	i = idx;
	while (str[++i])
	{
		if (ft_is_parens(str, i, is_special_char))
			i = get_end_parens(str, i, is_special_char, ")") + 1;
		if (ft_is_dollar_parens(str, i, is_special_char))
			i = get_end_dollar_parens(str, i, is_special_char, ")") + 1;
		if (is_special_char(str, idx, "`"))
			i = get_end_backquotes(str, idx, is_special_char, "`") + 1;
		if (is_special_char(str, i, "\""))
			i = get_end_doublequotes(str, i, is_special_char, "\"") + 1;
		if (!str[i - 1] || !str[i])
			return (idx + 1);
		if (is_special_char(str, i, chars))
		{
			if (str[i] == chars[0])
				return (i);
		}
	}
	return (i);
}

int	get_end_doublequotes(const char *str, int idx,
			bool (*is_special_char)(const char *str, int idx, char *chars),
			char *chars)
{
	int		i;

	i = idx;
	while (str[++i])
	{
		if (is_special_char(str, idx, "`"))
			i = get_end_backquotes(str, idx, is_special_char, "`") + 1;
		if (ft_is_dollar_parens(str, i, is_special_char))
			i = get_end_dollar_parens(str, i, is_special_char, ")") + 1;
		if (!str[i - 1] || !str[i])
			return (idx + 1);
		if (is_special_char(str, i, chars))
		{
			if (str[i] == chars[0])
				return (i);
		}
	}
	return (i);
}
