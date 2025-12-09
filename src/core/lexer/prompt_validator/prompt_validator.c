/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:02:05 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 17:51:15 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_validator_internal.h"

/**
 * # prompt_validator
 *
 * Runs all validators for nested
 * structures:
 * - single quotes
 * - normal parentheses
 * - double quotes
 * - `$()` (dollar-parens)
 * - backquotes
 *
 * Returns:
 * - index of the deepest error
 *   (smallest valid index)
 * - or -1 if everything is correct.
 *
 * Logic:
 * - Runs each validator separately.
 * - Stores the results in `checks`.
 * - Returns the smallest index
 *   using `ft_get_smaller`.
 */
int	ft_prompt_validator(const char *line)
{
	int	error_index;
	int	checks[5];

	error_index = -1;
	error_index = ft_validate_singlequotes(line);
	checks[0] = error_index;
	error_index = ft_validate_parens(line);
	checks[1] = error_index;
	error_index = ft_validate_doublequotes(line);
	checks[2] = error_index;
	error_index = ft_validate_dollar_parens(line);
	checks[3] = error_index;
	error_index = ft_validate_backquotes(line);
	checks[4] = error_index;
	return (ft_get_smaller(5, checks));
}
