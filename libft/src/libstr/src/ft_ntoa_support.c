/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ntoa_support.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:08:25 by valero            #+#    #+#             */
/*   Updated: 2025/09/28 21:17:55 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

int	ft_is_valid_base(char *base)
{
	int	i;
	int	i_verify_repeated;

	if (!base)
		return (0);
	i = -1;
	while (base[++i] != '\0')
	{
		if (!(base[i] > 32 && base[i] < 127)
			|| (base[i] == '+' || base[i] == '-'))
			return (0);
		i_verify_repeated = i;
		while (base[++i_verify_repeated] != '\0')
			if (base[i] == base[i_verify_repeated])
				return (0);
	}
	if (i < 2)
		return (0);
	return (1);
}

int	ft_nbrlen(unsigned long nbr, int base_len)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr /= base_len;
		len++;
	}
	return (len);
}
