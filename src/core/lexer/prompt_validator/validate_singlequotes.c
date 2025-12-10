/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_singlequotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:26:37 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 20:31:40 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

/**
 * # ft_validate_singlequotes
 *
 * Simple validation:
 * Single quotes never allow inner
 * nesting. You only need to check
 * for correct `'` pairs.
 */
int	ft_validate_singlequotes(const char *line)
{
	int		i;
	int		open_singlequotes_index;

	open_singlequotes_index = -1;
	i = -1;
	while (line[++i])
	{
		if (open_singlequotes_index == -1 && ft_is_special_char(line, i, "\""))
		{
			i = get_end(line, i, ft_is_special_char, "\"") + 1;
			if ((i && !line[i - 1]) || !line[i])
				return (open_singlequotes_index);
		}
		if (ft_is_special_char(line, i, "'"))
		{
			if (open_singlequotes_index == -1)
				open_singlequotes_index = i;
			else
				open_singlequotes_index = -1;
		}
	}
	return (open_singlequotes_index);
}
