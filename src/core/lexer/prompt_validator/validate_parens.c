/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:08:28 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 17:49:53 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

static void	jump_inner_structures(
				const char *line, int *idx,
				int *inner_openning_idx, int open_in_main);
static int	update_open_index(
				const char *line, int *open_idx,
				int *curr_idx, bool *is_dollar_parens);

/**
 * # ft_validate_parens
 *
 * Validates `(` and `)`, including interactions with `$()`.
 *
 * Logic:
 * - Distinguishes normal parentheses from dollar-parentheses.
 * - Uses `jump_inner_structures` to navigate inner blocks.
 */
int	ft_validate_parens(const char *line)
{
	int		i;
	int		open_parens_idx;
	int		other_open_idx[5];
	bool	is_dollar_parens;

	is_dollar_parens = false;
	fill_int_array(other_open_idx, 5, -1);
	open_parens_idx = -1;
	i = -1;
	while (line[++i])
	{
		if (open_parens_idx == -1 && ft_is_special_char(line, i, "\""))
			jump_quotes(line, &i);
		if (open_parens_idx > -1)
			jump_inner_structures(line, &i, other_open_idx, open_parens_idx);
		if ((i && !line[i - 1]) || !line[i])
			break ;
		if (ft_is_special_char(line, i, "()"))
			if (update_open_index(
					line, &open_parens_idx, &i, &is_dollar_parens) > -1)
				return (i);
	}
	if (open_parens_idx == -1)
		return (ft_get_smaller(4, other_open_idx));
	return (open_parens_idx);
}

/**
 * # jump_inner_structures (internal variations)
 *
 * Advances through inner structures when already inside
 * another structure. Prevents false positives.
 *
 * Types that can be skipped:
 * - double quotes
 * - single quotes
 * - parentheses
 * - backquotes
 * - `$()`
 */
static void	jump_inner_structures(
				const char *line, int *idx, int *openning_idx, int open_in_main)
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
 * # update_open_index
 *
 * Updates the open/close state of parentheses,
 * distinguishing normal parentheses from `$()`.
 *
 * ## Logic:
 * - If it finds a '(' preceded by '$',
 *   it enables `is_dollar_parens`.
 *
 * - If it finds a '(' that is not part of `$(`,
 *   it stores its index in `open_idx`
 *   and disables `is_dollar_parens`.
 *
 * - If it encounters a ')' while not in
 *   dollar-parens and with no recorded
 *   opening, it returns the index
 *   (unexpected closing).
 *
 * - If it encounters a ')' that matches
 *   the current opening, it resets
 *   `open_idx`.
 *
 * ## Return:
 * - index of the invalid closing,
 *   or -1 if everything is OK.
 */
static int	update_open_index(
			const char *line, int *open_idx,
			int *curr_idx, bool *is_dollar_parens)
{
	if (*curr_idx && ft_is_special_char(
			line, *curr_idx - 1, "$") && line[*curr_idx] == '(')
		*is_dollar_parens = true;
	if ((!*curr_idx && line[*curr_idx] == '(')
		|| (*curr_idx && line[*curr_idx - 1] != '$' && line[*curr_idx] == '('))
	{
		*open_idx = *curr_idx;
		*is_dollar_parens = false;
	}
	if (!*is_dollar_parens && *open_idx == -1 && line[*curr_idx] == ')')
		return (*curr_idx);
	if (*open_idx > -1 && line[*curr_idx] == ')')
		*open_idx = -1;
	return (-1);
}
