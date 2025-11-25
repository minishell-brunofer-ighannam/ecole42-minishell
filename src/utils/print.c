/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:41:00 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 22:43:31 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_print_bold_read(char *str, int fd)
{
	ft_putstr_fd(TEXT_BOLD TEXT_LIGHT_RED, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(TEXT_RESET, fd);
}
