/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_doublequotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:45:44 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 22:01:49 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

int	validate_doublequotes(const char *line)
{
	int	i;
	int	open_quote_index;
	int	other_openning_idx[2];

	other_openning_idx[0] = -1;
	other_openning_idx[1] = -1;
	open_quote_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_quote_index > -1)
		{
			if (ft_is_special_char(line, i, "`"))
			{
				other_openning_idx[0] = verify_char(ft_char_checker(line, i, "`", ft_is_special_char), validate_backquotes);
				if (other_openning_idx[0] > -1)
					other_openning_idx[0] = (i + other_openning_idx[0]);
				else
					i = get_end(line, i, ft_is_special_char, "\"") + 1;
			}
			else if (ft_is_special_char(line, i, "$") && line[i + 1] == '(')
			{
				other_openning_idx[1] = verify_char(ft_char_checker(line, i, ")", ft_is_special_char), validate_dollar_parens);
				if (other_openning_idx[1] > -1)
					other_openning_idx[1] = i + other_openning_idx[1];
				else
					i = get_end(line, i, ft_is_special_char, ")") + 1;
			}
			if (!line[i])
				break ;
		}
		if (ft_is_special_char(line, i, "\""))
		{
			if (open_quote_index == -1)
				open_quote_index = i;
			else
				open_quote_index = -1;
		}
	}
	if (open_quote_index == -1)
		return (ft_get_smaller(2, other_openning_idx));
	return (open_quote_index);
}
