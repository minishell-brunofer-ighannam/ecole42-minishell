/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_jump.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 08:55:01 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/19 12:59:39 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

void	jump_to_closing(
	const char *line, int *idx,
	int *inner_openning_idx, int (*validate)(const char *line))
{
	char	structure[2];

	structure[1] = 0;
	if (validate == validate_doublequotes)
		structure[0] = '"';
	if (validate == validate_parens || validate == validate_dollar_parens)
		structure[0] = ')';
	if (validate == validate_backquotes)
		structure[0] = '`';
	if (validate == validate_singlequotes)
		structure[0] = '\'';
	*inner_openning_idx = verify_char(
			ft_char_checker(line, *idx, (char *)structure, ft_is_special_char),
			validate);
	if (*inner_openning_idx > -1)
		*inner_openning_idx = *idx + *inner_openning_idx;
	else
		*idx = get_end(line, *idx, ft_is_special_char, (char *)structure) + 1;
}
