/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 07:02:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/09/26 21:41:18 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

static int		index_of(const char *str, const char target);
static int		is_valid_base(const char *base);
static long int	conversion(const char *nbstr, const char *base);

int	ft_atoi_base(const char *nptr, const char *base)
{
	long int	result;
	int			sign;

	if (!is_valid_base(base))
		return (0);
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	sign = 1;
	if (nptr[0] == '-' || nptr[0] == '+')
	{
		if (nptr[0] == '-')
			sign = -1;
		nptr++;
	}
	result = conversion(nptr, base);
	result = result * sign;
	if (result > INT_MAX)
		return (INT_MAX);
	else if (result < INT_MIN)
		return (INT_MIN);
	return ((int)result);
}

static int	index_of(const char *str, const char target)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == target)
			return (i);
	return (-1);
}

static int	is_valid_base(const char *base)
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

static long int	conversion(const char *nbstr, const char *base)
{
	long int	result;
	int			len_base;
	int			index;
	int			i;

	result = 0;
	len_base = ft_strlen(base);
	i = -1;
	while (nbstr[++i])
	{
		index = index_of(base, nbstr[i]);
		if (index < 0)
			break ;
		result = result * len_base + index;
	}
	return (result);
}
