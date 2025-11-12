/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 23:01:58 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 23:33:26 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils_internal.h"

void	print_structure_not_closed_error(char *src, int error_idx)
{
	int	i;

	if (!src || error_idx < 0)
		return ;
	i = -1;
	while (src[++i] && i < error_idx + error_idx)
	{
		// TEXT_LIGHT_RED
		if (i != error_idx)
			ft_putchar_fd(src[i], 2);
		else
		{
			ft_putstr_fd(TEXT_BOLD, 2);
			ft_putstr_fd(TEXT_LIGHT_RED, 2);
			ft_putchar_fd(src[i], 2);
			ft_putstr_fd(TEXT_RESET, 2);
		}
	}
	ft_putchar_fd('\n', 2);
	i = -1;
	while (src[++i] && i < error_idx + 2)
	{
		if (i != error_idx)
			ft_putchar_fd(' ', 2);
		else
		{
			ft_putstr_fd(TEXT_BOLD, 2);
			ft_putstr_fd(TEXT_LIGHT_RED, 2);
			ft_putchar_fd('^', 2);
			ft_putstr_fd(TEXT_RESET, 2);
		}
	}
	ft_putstr_fd(TEXT_LIGHT_RED, 2);
	ft_putstr_fd("syntax error: structure not closed\n", 2);
	ft_putstr_fd(TEXT_RESET, 2);
}
