/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:02:05 by valero            #+#    #+#             */
/*   Updated: 2025/11/17 00:12:50 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

int	prompt_validator(const char *line)
{
	int	error_index;
	int	checks[5];

	error_index = -1;
	error_index = validate_singlequotes(line);
	checks[0] = error_index;
	error_index = validate_parens(line);
	checks[1] = error_index;
	error_index = validate_doublequotes(line);
	checks[2] = error_index;
	error_index = validate_dollar_parens(line);
	checks[3] = error_index;
	error_index = validate_backquotes(line);
	checks[4] = error_index;
	return (ft_get_smaller(5, checks));
}
