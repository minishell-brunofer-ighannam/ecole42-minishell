/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:49:18 by brunofer          #+#    #+#             */
/*   Updated: 2025/07/18 07:13:20 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

static int		nbrlen(long int nbr, int is_negative);
static void		number_to_string(long int nbr, int nbr_len,
					int is_negative, char *str_nbr);
static void		handle_negative(int *is_negative, long int *nbr);

char	*ft_itoa(int n)
{
	long int	nbr;
	int			nbr_len;
	int			is_negative;
	char		*str_nbr;

	nbr = (long int)n;
	handle_negative(&is_negative, &nbr);
	nbr_len = nbrlen(nbr, is_negative);
	if (nbr == 0)
		return (ft_strdup("0"));
	str_nbr = malloc(nbr_len + 1);
	if (!str_nbr)
		return (NULL);
	number_to_string(nbr, nbr_len, is_negative, str_nbr);
	return (str_nbr);
}

static void	handle_negative(int *is_negative, long int *nbr)
{
	if (*nbr < 0)
	{
		*nbr *= -1;
		*is_negative = 1;
	}
	else
		*is_negative = 0;
}

static int	nbrlen(long int nbr, int is_negative)
{
	int	len;

	len = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len + is_negative);
}

static void	number_to_string(long int nbr, int nbr_len,
		int is_negative, char *str_nbr)
{
	int	last_digit;

	last_digit = 0;
	if (is_negative)
		str_nbr[0] = '-';
	str_nbr[nbr_len] = '\0';
	while (nbr_len-- - is_negative)
	{
		last_digit = nbr % 10;
		str_nbr[nbr_len] = last_digit + '0';
		nbr /= 10;
	}
}
