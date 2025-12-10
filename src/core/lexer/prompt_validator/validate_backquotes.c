/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_backquotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:09:09 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 17:53:13 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

static void	jump_inner_structures(
				const char *line, int *idx,
				int *inner_openning_idx, int open_in_main);
static void	update_open_index(int *open_idx, int curr_idx);

/**
 * # ft_validate_backquotes
 *
 * Checks whether backquotes are properly
 * opened and closed. Also detects inner
 * structures that may cause errors.
 *
 * Logic:
 * - Scans the text, alternating between
 *   “open/closed” states.
 * - If it finds inner structures, it
 *   delegates to `jump_inner_structures`.
 * - Returns the error index, or -1 if
 *   everything is valid.
 */
int	ft_validate_backquotes(const char *line)
{
	int		i;
	int		open_backquotes_index;
	int		other_openning_idx[4];

	fill_int_array(other_openning_idx, 4, -1);
	open_backquotes_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_backquotes_index == -1 && ft_is_special_char(line, i, "\""))
			jump_quotes(line, &i);
		if (open_backquotes_index > -1)
			jump_inner_structures(
				line, &i, other_openning_idx, open_backquotes_index);
		if ((i && !line[i - 1]) || !line[i])
			break ;
		if (ft_is_special_char(line, i, "`"))
			update_open_index(&open_backquotes_index, i);
	}
	if (open_backquotes_index == -1)
		return (ft_get_smaller(3, other_openning_idx));
	return (open_backquotes_index);
}

/**
 * # jump_inner_structures (internal variations)
 *
 * Advances through inner structures when
 * already inside another structure.
 * Prevents false positives.
 *
 * Types that can be skipped:
 * - double quotes
 * - single quotes
 * - parentheses
 * - backquotes
 * - `$()`
 */
static void	jump_inner_structures(
				const char *line, int *idx,
				int *inner_openning_idx, int open_in_main)
{
	if (ft_is_special_char(line, *idx, "\""))
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				inner_openning_idx + 0, ft_validate_doublequotes),
			open_in_main);
	if (ft_is_special_char(line, *idx, "'"))
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				inner_openning_idx + 1, ft_validate_singlequotes),
			open_in_main);
	else if (ft_is_special_char(line, *idx, "()"))
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				inner_openning_idx + 2, ft_validate_parens),
			open_in_main);
	else if (ft_is_special_char(line, *idx, "$") && line[*idx + 1] == '(')
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				inner_openning_idx + 3, ft_validate_dollar_parens),
			open_in_main);
}

/**
 * # update_open_index (simple version)
 *
 * Toggles the open/close state of simple
 * structures such as quotes or
 * backquotes.
 */
static void	update_open_index(int *open_idx, int curr_idx)
{
	if (*open_idx == -1)
		*open_idx = curr_idx;
	else
		*open_idx = -1;
}
