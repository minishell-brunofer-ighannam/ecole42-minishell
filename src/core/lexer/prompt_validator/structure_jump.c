/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_jump.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:55:01 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/09 19:48:28 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

static char	ft_get_corresponding_closing(const char *str);
static void	ft_update_indexes(
				t_jump_to_closing_params params,
				int open_in_main, char structure[2]);

/**
 * # jump_to_closing
 *
 * Key function for navigating nested
 * structures. Advances the index until
 * the correct closing character,
 * respecting the structure type
 * (", ', `, (), $()).
 *
 * Logic:
 * - Determines the closing character.
 * - Uses `verify_char` to detect errors
 *   inside the block.
 * - If no internal error is found,
 *   jumps directly to `get_end`.
 */
void	jump_to_closing(
	t_jump_to_closing_params params,
	int open_in_main)
{
	char	structure[2];
	bool	is_dollar_parens;

	is_dollar_parens = params.validate == ft_validate_dollar_parens;
	structure[1] = 0;
	if (params.validate == ft_validate_doublequotes)
		structure[0] = '"';
	if (params.validate == ft_validate_parens || is_dollar_parens)
		structure[0] = ')';
	if (params.validate == ft_validate_backquotes)
		structure[0] = '`';
	if (params.validate == ft_validate_singlequotes)
		structure[0] = '\'';
	*params.inner_openning_idx = verify_char(
			ft_char_checker(params.line, *params.idx,
				(char *)structure, ft_is_special_char),
			params.validate);
	if (*params.inner_openning_idx > -1)
		ft_update_indexes(params, open_in_main, structure);
	else
		*params.idx = get_end(params.line, *params.idx,
				ft_is_special_char, (char *)structure) + 1;
}

t_jump_to_closing_params	ft_create_jump_to_closing_params(
								const char *line, int *idx,
								int *inner_openning_idx,
								int (*validate)(const char *line))
{
	t_jump_to_closing_params	params;

	params.line = line;
	params.idx = idx;
	params.inner_openning_idx = inner_openning_idx;
	params.validate = validate;
	return (params);
}

static void	ft_update_indexes(
				t_jump_to_closing_params params,
				int open_in_main, char structure[2])
{
	int		tmp;
	bool	is_dollar_parens;
	char	start_corresp_closing;

	start_corresp_closing = ft_get_corresponding_closing(
			params.line + open_in_main);
	is_dollar_parens = params.validate == ft_validate_dollar_parens;
	tmp = *params.inner_openning_idx;
	if (is_dollar_parens)
		tmp--;
	if (*params.inner_openning_idx
		&& params.line[*params.inner_openning_idx + *params.idx]
		== start_corresp_closing)
		*params.inner_openning_idx = open_in_main
			+ *params.inner_openning_idx + (int)is_dollar_parens;
	else
		*params.inner_openning_idx = *params.idx + *params.inner_openning_idx;
	if (tmp + *params.idx > *params.idx)
	{
		structure[0] = start_corresp_closing;
		*params.idx = get_end(params.line, open_in_main,
				ft_is_special_char, (char *)structure) - 1;
	}
}

void	jump_quotes(const char *line, int *idx)
{
	if (ft_is_special_char(line, *idx, "\""))
		*idx = get_end(line, *idx, ft_is_special_char, "\"") + 1;
	if (*idx && !line[*idx - 1])
		(*idx)--;
	if (ft_is_special_char(line, *idx, "'"))
		*idx = get_end(line, *idx, ft_is_special_char, "'") + 1;
	if (*idx && !line[*idx - 1])
		(*idx)--;
}

static char	ft_get_corresponding_closing(const char *str)
{
	if (str[0] == '\"')
		return ('"');
	if (str[0] == '\'')
		return ('\'');
	if (str[0] == '`')
		return ('`');
	if (str[0] == '(')
		return (')');
	if (str[0] == '$' && str[1] == '(')
		return (')');
	return (0);
}
