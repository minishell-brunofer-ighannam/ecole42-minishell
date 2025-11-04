/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 07:02:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/18 19:44:07 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int				size;
	unsigned int	len_str;
	char			*sub;

	if ((!s && !start))
		return (NULL);
	len_str = (unsigned int)ft_strlen(s);
	if (!s || (start > len_str))
	{
		sub = (char *)malloc(1);
		sub[0] = 0;
		return (sub);
	}
	size = len;
	if (len > (len_str - start))
		size = len_str - start;
	sub = (char *)malloc(size + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, &s[start], size + 1);
	return (sub);
}
