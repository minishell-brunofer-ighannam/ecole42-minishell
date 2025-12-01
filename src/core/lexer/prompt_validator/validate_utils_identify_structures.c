/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils_identify_structures.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 21:43:30 by valero            #+#    #+#             */
/*   Updated: 2025/11/29 21:59:30 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

bool	ft_is_parens(const char *str, int idx,
			bool (*is_special_char)(const char *str, int idx, char *chars))
{
	return (
		(!idx && is_special_char(str, idx, "("))
		|| (idx && is_special_char(str, idx, "(")
			&& !is_special_char(str, idx - 1, "$"))
	);
}

bool	ft_is_dollar_parens(const char *str, int idx,
				bool (*is_special_char)(const char *str, int idx, char *chars))
{
	return (
		idx + 1 && is_special_char(str, idx, "$")
		&& str[idx + 1] == '('
	);
}
