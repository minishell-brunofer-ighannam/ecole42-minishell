/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils_get_end_skip_inner.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:14:45 by valero            #+#    #+#             */
/*   Updated: 2025/12/08 15:29:11 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

void	ft_skip_inner_of_dollar_parens(
			const char *str, int *i, int idx,
			bool (*is_special_char)(const char *str, int idx, char *chars))
{
	if (ft_is_parens(str, *i, is_special_char))
		*i = get_end_parens(str, *i, is_special_char, ")") + 1;
	if (is_special_char(str, idx, "`"))
		*i = get_end_backquotes(str, idx, is_special_char, "`") + 1;
	if (is_special_char(str, *i, "\""))
		*i = get_end_doublequotes(str, *i, is_special_char, "\"") + 1;
}

void	ft_skip_inner_of_parens(
			const char *str, int *i, int idx,
			bool (*is_special_char)(const char *str, int idx, char *chars))
{
	if (ft_is_dollar_parens(str, *i, is_special_char))
		*i = get_end_dollar_parens(str, *i, is_special_char, ")") + 1;
	if (is_special_char(str, idx, "`"))
		*i = get_end_backquotes(str, idx, is_special_char, "`") + 1;
	if (is_special_char(str, *i, "\""))
		*i = get_end_doublequotes(str, *i, is_special_char, "\"") + 1;
}
