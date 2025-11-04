/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tolower.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:41:18 by brunofer          #+#    #+#             */
/*   Updated: 2025/09/29 14:14:05 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

char	*ft_str_tolower(const char *str)
{
	int		i;
	int		len_str;
	char	*new_str;

	if (!str)
		return (NULL);
	len_str = ft_strlen(str);
	new_str = (char *)malloc((len_str + 1) * sizeof(char));
	new_str[len_str] = '\0';
	i = -1;
	while (str[++i])
		new_str[i] = ft_tolower(str[i]);
	return (new_str);
}
