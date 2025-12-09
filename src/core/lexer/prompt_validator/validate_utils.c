/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:48:52 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:04:59 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

/**
 * # verify_char
 *
 * Extracts a substring representing a delimited structure
 * and passes it to the corresponding validator.
 *
 * Behavior:
 * - Builds a substring using `get_end` as the end index.
 * - Calls the validator on that substring.
 * - If the validator finds an error, returns the relative index.
 */
int	verify_char(t_char_checker checker, int (*verify)(const char *line))
{
	char	*sub;
	int		openning_idx;

	sub = ft_substr(checker.str, checker.idx,
			get_end(checker.str, checker.idx,
				checker.is_special_char, checker.chars) + 1 - checker.idx);
	openning_idx = verify(sub);
	free(sub);
	if (openning_idx > -1)
		return (openning_idx);
	return (-1);
}

/**
 * # ft_char_checker
 *
 * Initializes a `t_char_checker` with the necessary data
 * for validating internal structures.
 */
t_char_checker	ft_char_checker(const char *str, int idx, char *chars,
					bool (*is_special_char)(
						const char *str, int idx, char *chars))
{
	t_char_checker	checker;

	checker.str = str;
	checker.idx = idx;
	checker.chars = chars;
	checker.is_special_char = is_special_char;
	return (checker);
}

/**
 * # ft_get_smaller
 *
 * Given an array of indices, returns the
 * smallest valid index (>= 0). If all
 * are invalid, returns -1.
 *
 * Used to decide which error has
 * priority.
 */
int	ft_get_smaller(int len, int *arr)
{
	int	smaller;

	smaller = INT_MAX;
	while (--len >= 0)
		if (arr[len] >= 0 && arr[len] < smaller)
			smaller = arr[len];
	if (smaller == INT_MAX)
		return (-1);
	return (smaller);
}

/**
 * # fill_int_array
 *
 * Initializes an integer array with a
 * single value.
 * Simple utility for preparing index
 * arrays.
 */
void	fill_int_array(int *array, int len, int value)
{
	while (--len >= 0)
		array[len] = value;
}
