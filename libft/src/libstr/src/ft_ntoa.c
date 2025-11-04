/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ntoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:03:29 by valero            #+#    #+#             */
/*   Updated: 2025/09/28 21:45:48 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

static void	handle_base(char *result, char *base,
				int len_nbr, unsigned long number);

char	*ft_itoa_base(int nbr, char *base)
{
	int			is_negative;
	long int	number;
	int			len_nbr;
	char		*result;

	if (!ft_is_valid_base(base))
		return (NULL);
	if (!nbr)
		return (ft_strdup("0"));
	number = (long int)nbr;
	is_negative = 0;
	if (number < 0)
	{
		is_negative = 1;
		number *= -1;
	}
	len_nbr = ft_nbrlen((unsigned long)number, ft_strlen(base)) + is_negative;
	result = (char *)malloc(len_nbr + 1);
	if (!result)
		return (NULL);
	handle_base(result, base, len_nbr, (unsigned long)number);
	if (is_negative)
		result[0] = '-';
	result[len_nbr] = '\0';
	return (result);
}

char	*ft_utoa_base(unsigned int nbr, char *base)
{
	int			len_nbr;
	char		*result;

	if (!ft_is_valid_base(base))
		return (NULL);
	if (!nbr)
		return (ft_strdup("0"));
	len_nbr = ft_nbrlen((unsigned long)nbr, ft_strlen(base));
	result = (char *)malloc(len_nbr + 1);
	if (!result)
		return (NULL);
	handle_base(result, base, len_nbr, (unsigned long)nbr);
	result[len_nbr] = '\0';
	return (result);
}

char	*ft_ultoa_base(unsigned long nbr, char *base)
{
	int			len_nbr;
	char		*result;

	if (!ft_is_valid_base(base))
		return (NULL);
	if (!nbr)
		return (ft_strdup("0"));
	len_nbr = ft_nbrlen(nbr, ft_strlen(base));
	result = (char *)malloc(len_nbr + 1);
	if (!result)
		return (NULL);
	handle_base(result, base, len_nbr, nbr);
	result[len_nbr] = '\0';
	return (result);
}

static void	handle_base(char *result, char *base,
				int len_nbr, unsigned long number)
{
	int	len_base;

	len_base = ft_strlen(base);
	while (len_nbr--)
	{
		result[len_nbr] = base[number % len_base];
		number /= len_base;
	}
}
