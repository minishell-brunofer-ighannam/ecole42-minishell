/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:14:44 by valero            #+#    #+#             */
/*   Updated: 2025/11/07 15:17:46 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

char	*status(bool test_ok)
{
	if (test_ok)
		return (PRINT_BOLD PRINT_LIGHT_GREEN"OK"PRINT_RESET);
	return (PRINT_BOLD PRINT_LIGHT_RED"ERROR"PRINT_RESET);
}
