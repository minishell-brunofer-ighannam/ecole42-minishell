/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_ishexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:24:21 by brunofer          #+#    #+#             */
/*   Updated: 2025/09/28 22:44:57 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

int	ft_str_ishexa(const char *hex, const char *prefix)
{
	int	i;

	if (!hex || !hex[0])
		return (0);
	i = 0;
	if (prefix)
	{
		i = -1;
		while (prefix[++i])
			if (hex[i] != prefix[i])
				return (0);
	}
	if (!hex[i])
		return (0);
	while (hex[i])
		if (!ft_strchr(HEXA_BASE, ft_tolower(hex[i++])))
			return (0);
	return (1);
}
