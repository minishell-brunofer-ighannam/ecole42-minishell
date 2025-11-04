/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 07:02:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/18 19:44:07 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	big_i;
	int		ltt_i;

	if ((!big) && !len)
		return (NULL);
	if (!ft_strlen(little))
		return ((char *)big);
	big_i = -1;
	while (big[++big_i] && (big_i < len))
	{
		ltt_i = 0;
		if (big[big_i] == little[0])
		{
			while ((little[ltt_i] && (big[big_i + ltt_i] == little[ltt_i]))
				&& (big_i + ltt_i) < len)
				ltt_i++;
		}
		if (!little[ltt_i])
			return ((char *)&big[big_i]);
	}
	return (NULL);
}
