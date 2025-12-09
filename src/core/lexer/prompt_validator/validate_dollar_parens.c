/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dollar_parens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 04:32:23 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 17:54:21 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

static void	jump_inner_structures(
				const char *line, int *idx,
				int *openning_idx, int open_in_main);
static int	update_open_index(
				const char *line, int *open_idx,
				int *curr_idx, bool *is_parens);

/**
 * # ft_validate_dollar_parens
 *
 * Validates `$()` structures,
 * including nesting.
 *
 * Logic:
 * - Detects the start with `$(` and
 *   the end with `)`.
 * - Tracks inner depth using
 *   `jump_inner_structures`.
 * - Returns the nearest error
 *   position, if any.
 */
int	ft_validate_dollar_parens(const char *line)
{
	int		i;
	int		open_dolparens_idx;
	int		other_open_idx[5];
	bool	is_parens;

	is_parens = false;
	fill_int_array(other_open_idx, 5, -1);
	open_dolparens_idx = -1;
	i = -1;
	while (line[++i])
	{
		if (open_dolparens_idx == -1 && ft_is_special_char(line, i, "\""))
			jump_quotes(line, &i);
		if (open_dolparens_idx > -1)
			jump_inner_structures(line, &i, other_open_idx, open_dolparens_idx);
		if ((i && !line[i - 1]) || !line[i])
			break ;
		if (ft_is_special_char(line, i, "()"))
			if (update_open_index(
					line, &open_dolparens_idx, &i, &is_parens) > -1)
				return (i);
	}
	if (open_dolparens_idx == -1)
		return (ft_get_smaller(4, other_open_idx));
	return (open_dolparens_idx);
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
				int *openning_idx, int open_in_main)
{
	if (ft_is_special_char(line, *idx, "\""))
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				openning_idx + 0, ft_validate_doublequotes),
			open_in_main);
	if (ft_is_special_char(line, *idx, "'"))
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				openning_idx + 1, ft_validate_singlequotes),
			open_in_main);
	else if (ft_is_special_char(line, *idx, "("))
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				openning_idx + 2, ft_validate_parens),
			open_in_main);
	else if (ft_is_special_char(line, *idx, "`"))
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				openning_idx + 3, ft_validate_backquotes),
			open_in_main);
	else if (ft_is_special_char(line, *idx, "$") && line[*idx + 1] == '(')
		jump_to_closing(
			ft_create_jump_to_closing_params(line, idx,
				openning_idx + 4, ft_validate_dollar_parens),
			open_in_main);
}

/**
 * # update_open_index (dollar-parens version)
 *
 * Handles the more elaborate `$(` logic:
 * - identifies special behavior when
 *   preceded by '$'
 * - tracks whether the current block is
 *   really a `$()` block
 * - returns an error if a `)` closes
 *   incorrectly
 */
static int	update_open_index(
				const char *line, int *open_idx, int *curr_idx, bool *is_parens)
{
	if (*curr_idx && !ft_is_special_char(line, *curr_idx - 1, "$"))
		*is_parens = true;
	if (*curr_idx && ft_is_special_char(
			line, *curr_idx - 1, "$") && line[*curr_idx] == '(')
	{
		*open_idx = (*curr_idx)++;
		*is_parens = false;
		if (!line[*curr_idx])
			return (--(*curr_idx));
	}
	if (!*is_parens && *open_idx == -1 && line[*curr_idx] == ')')
		return (*curr_idx);
	if (*open_idx > -1 && line[*curr_idx] == ')')
		*open_idx = -1;
	return (-1);
}
