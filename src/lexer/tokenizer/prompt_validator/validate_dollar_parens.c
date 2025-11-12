/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dollar_parens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:59:55 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 22:07:11 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

int	validate_dollar_parens(const char *line)
{
	int		i;
	int		open_dollar_parens_index;
	int		other_openning_idx[4];
	bool	is_parens;

	is_parens = false;
	other_openning_idx[0] = -1;
	other_openning_idx[1] = -1;
	other_openning_idx[2] = -1;
	other_openning_idx[3] = -1;
	open_dollar_parens_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_dollar_parens_index > -1)
		{
			if (ft_is_special_char(line, i, "\""))
			{
				other_openning_idx[0] = verify_char(ft_char_checker(line, i, "\"", ft_is_special_char), validate_doublequotes);
				if (other_openning_idx[0] > -1)
					other_openning_idx[0] = i + other_openning_idx[0];
				else
					i = get_end(line, i, ft_is_special_char, "\"") + 1;
			}
			else if (ft_is_special_char(line, i, "("))
			{
				other_openning_idx[1] = verify_char(ft_char_checker(line, i, ")", ft_is_special_char), validate_parens);
				if (other_openning_idx[1] > -1)
					other_openning_idx[1] = i + other_openning_idx[1];
				else
					i = get_end(line, i, ft_is_special_char, ")") + 1;
			}
			else if (ft_is_special_char(line, i, "`"))
			{
				other_openning_idx[2] = verify_char(ft_char_checker(line, i, "`", ft_is_special_char), validate_backquotes);
				if (other_openning_idx[2] > -1)
					other_openning_idx[2] = i + other_openning_idx[2];
				else
					i = get_end(line, i, ft_is_special_char, "\"") + 1;
			}
			else if (ft_is_special_char(line, i, "$") && line[i + 1] == '(')
			{
				other_openning_idx[3] = verify_char(ft_char_checker(line, i, ")", ft_is_special_char), validate_dollar_parens);
				if (other_openning_idx[3] > -1)
					other_openning_idx[3] = i + other_openning_idx[3];
				else
					i = get_end(line, i, ft_is_special_char, ")") + 1;
			}
			if (!line[i])
				break ;
		}
		if (ft_is_special_char(line, i, "()"))
		{
			if (i && !ft_is_special_char(line, i - 1, "$"))
				is_parens = true;
			if (i && ft_is_special_char(line, i - 1, "$") && line[i] == '(')
			{
				open_dollar_parens_index = i++;
				is_parens = false;
			}
			if (!is_parens && open_dollar_parens_index == -1 && line[i] == ')')
				return (i);
			if (open_dollar_parens_index && line[i] == ')')
				open_dollar_parens_index = -1;
		}
	}
	if (open_dollar_parens_index == -1)
		return (ft_get_smaller(4, other_openning_idx));
	return (open_dollar_parens_index);
}
