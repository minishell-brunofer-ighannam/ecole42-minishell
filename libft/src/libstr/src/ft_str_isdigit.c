/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:18:14 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/09 02:52:40 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

int	ft_str_isdigit(const char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
		if (!ft_isdigit(nbr[i++]))
			return (0);
	return (1);
}
