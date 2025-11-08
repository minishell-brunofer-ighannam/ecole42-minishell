/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:14:44 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 17:20:42 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

char	*status(bool test_ok)
{
	if (test_ok)
		return (PRINT_BOLD PRINT_LIGHT_GREEN"OK"PRINT_RESET);
	return (PRINT_BOLD PRINT_LIGHT_RED"ERROR"PRINT_RESET);
}

void	print_test_and_result(
			t_test test, void (*print_result)(void *arg), void *arg)
{
	printf("test %d: %s  ", test.teste_number, status(test.test_ok));
	printf("%s%s%s\n", PRINT_LIGHT_BLACK,
		test.test_input, PRINT_BOLD PRINT_GRAY_233);
	printf("%s%s", " >> Result: ", PRINT_RESET PRINT_GRAY_233);
	print_result(arg);
	printf("\n"PRINT_RESET);
}
