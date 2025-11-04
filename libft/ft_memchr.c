/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 07:02:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/07/26 14:29:15 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	target_char;
	unsigned char	*ptr;
	size_t			i;

	target_char = (unsigned char)c;
	ptr = (unsigned char *)s;
	i = -1;
	while (++i < n)
	{
		if ((unsigned char)ptr[i] == target_char)
			return (&ptr[i]);
	}
	return (NULL);
}
