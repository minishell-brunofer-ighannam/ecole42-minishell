/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_singlequotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:56:18 by valero            #+#    #+#             */
/*   Updated: 2025/11/21 15:00:13 by brunofer         ###   ########.fr       */
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
