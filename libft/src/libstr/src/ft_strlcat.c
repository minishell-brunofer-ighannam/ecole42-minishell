/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 07:02:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/18 19:44:07 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	if ((!dst || !src) && !size)
		return (0);
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if ((size <= len_dst) || !size)
		return (len_src + size);
	i = -1;
	while (src[++i] && ((len_dst + i) < (size - 1)))
		dst[len_dst + i] = src[i];
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
