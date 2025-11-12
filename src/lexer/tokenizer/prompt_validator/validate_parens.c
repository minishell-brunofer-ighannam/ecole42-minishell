/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:05:08 by valero            #+#    #+#             */
/*   Updated: 2025/11/12 11:49:19 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

static void	jump_inner_structures(
				const char *line, int *idx, int *inner_openning_idx);
static int	update_open_index(
				const char *line, int *open_idx,
				int *curr_idx, bool *is_dollar_parens);

int	validate_parens(const char *line)
{
	int		i;
	int		open_parens_index;
	int		other_openning_idx[4];
	bool	is_dollar_parens;

	is_dollar_parens = false;
	fill_int_array(other_openning_idx, 4, -1);
	open_parens_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_parens_index > -1)
			jump_inner_structures(line, &i, other_openning_idx);
		if (!line[i])
			break ;
		if (ft_is_special_char(line, i, "()"))
			if (update_open_index(
					line, &open_parens_index, &i, &is_dollar_parens) > -1)
				return (i);
	}
	if (open_parens_index == -1)
		return (ft_get_smaller(4, other_openning_idx));
	return (open_parens_index);
}

static void	jump_inner_structures(const char *line, int *idx, int *openning_idx)
{
	if (ft_is_special_char(line, *idx, "\""))
		jump_to_closing(line, idx, openning_idx + 0, validate_doublequotes);
	else if (ft_is_special_char(line, *idx, "("))
		jump_to_closing(line, idx, openning_idx + 1, validate_parens);
	else if (ft_is_special_char(line, *idx, "`"))
		jump_to_closing(line, idx, openning_idx + 2, validate_backquotes);
	else if (ft_is_special_char(line, *idx, "$") && line[*idx + 1] == '(')
		jump_to_closing(line, idx, openning_idx + 3, validate_dollar_parens);
}

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
	if (*open_idx && line[*curr_idx] == ')')
		*open_idx = -1;
	return (-1);
}
