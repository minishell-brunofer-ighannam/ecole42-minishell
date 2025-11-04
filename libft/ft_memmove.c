/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 07:02:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/07/27 11:41:19 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*target;
	unsigned char	*origin;

	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	target = (unsigned char *)dest;
	origin = (unsigned char *)src;
	i = -1;
	if (target > origin)
	{
		i = n;
		while (i--)
		{
			target[i] = origin[i];
			if (i == 0)
				break ;
		}
		return (target);
	}
	return (ft_memcpy(target, origin, n));
}
