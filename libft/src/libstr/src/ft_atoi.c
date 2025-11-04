/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 07:02:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/20 18:01:34 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

int	ft_atoi(const char *nptr)
{
	int		result;
	int		i;
	int		sign;
	char	*nbstr;

	nbstr = (char *)nptr;
	if (!ft_strncmp("-2147483648", nbstr, 11))
		return (INT_MIN);
	while (*nbstr == ' ' || (*nbstr > 8 && *nbstr < 14))
		nbstr++;
	sign = 1;
	if (nbstr[0] == '-' || nbstr[0] == '+')
	{
		if (nbstr[0] == '-')
			sign = -1;
		nbstr++;
	}
	result = 0;
	i = -1;
	while (ft_isdigit(nbstr[++i]))
		result = result * 10 + (nbstr[i] - '0');
	return (result * sign);
}
