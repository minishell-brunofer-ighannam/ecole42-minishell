/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:02:05 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 23:45:11 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

int	prompt_validator(const char *line)
{
	int	error_index;

	error_index = -1;
	error_index = validate_parens(line);
	if (error_index > -1)
		return (error_index);
	error_index = validate_doublequotes(line);
	if (error_index > -1)
		return (error_index);
	error_index = validate_dollar_parens(line);
	if (error_index > -1)
		return (error_index);
	error_index = validate_backquotes(line);
	if (error_index > -1)
		return (error_index);
	return (error_index);
}
