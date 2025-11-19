/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dollar_parens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:59:55 by valero            #+#    #+#             */
/*   Updated: 2025/11/19 15:19:57 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

static void	jump_inner_structures(
				const char *line, int *idx, int *openning_idx);
static int	update_open_index(
				const char *line, int *open_idx,
				int *curr_idx, bool *is_parens);

int	validate_dollar_parens(const char *line)
{
	int		i;
	int		open_dollar_parens_index;
	int		other_openning_idx[5];
	bool	is_parens;

	is_parens = false;
	fill_int_array(other_openning_idx, 5, -1);
	open_dollar_parens_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_dollar_parens_index > -1)
			jump_inner_structures(line, &i, other_openning_idx);
		if (!line[i])
			break ;
		if (ft_is_special_char(line, i, "()"))
			if (update_open_index(
					line, &open_dollar_parens_index, &i, &is_parens) > -1)
				return (i);
	}
	if (open_dollar_parens_index == -1)
		return (ft_get_smaller(4, other_openning_idx));
	return (open_dollar_parens_index);
}

static void	jump_inner_structures(const char *line, int *idx, int *openning_idx)
{
	if (ft_is_special_char(line, *idx, "\""))
		jump_to_closing(line, idx, openning_idx + 0, validate_doublequotes);
	if (ft_is_special_char(line, *idx, "'"))
		jump_to_closing(line, idx, openning_idx + 1, validate_singlequotes);
	else if (ft_is_special_char(line, *idx, "("))
		jump_to_closing(line, idx, openning_idx + 2, validate_parens);
	else if (ft_is_special_char(line, *idx, "`"))
		jump_to_closing(line, idx, openning_idx + 3, validate_backquotes);
	else if (ft_is_special_char(line, *idx, "$") && line[*idx + 1] == '(')
		jump_to_closing(line, idx, openning_idx + 4, validate_dollar_parens);
}

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
	}
	if (!*is_parens && *open_idx == -1 && line[*curr_idx] == ')')
		return (*curr_idx);
	if (*open_idx && line[*curr_idx] == ')')
		*open_idx = -1;
	return (-1);
}
