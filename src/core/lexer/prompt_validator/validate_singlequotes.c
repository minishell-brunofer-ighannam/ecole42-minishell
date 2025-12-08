/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_singlequotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:26:37 by valero            #+#    #+#             */
/*   Updated: 2025/12/08 15:26:41 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

/**
 * # ft_validate_singlequotes
 *
 * Validação simples:
 * Aspas simples nunca permitem aninhamento interno.
 * Basta verificar pares corretos de `'`.
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
			if (!line[i])
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
