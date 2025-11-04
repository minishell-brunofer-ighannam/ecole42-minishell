/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:48:54 by valero            #+#    #+#             */
/*   Updated: 2025/09/28 22:36:24 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

static void	tmp_strcpy(char *target, char *src, size_t size);

char	*ft_str_addprefix(char *src, char *prefix, int free_src)
{
	char	*new_str;
	size_t	src_len;
	size_t	prefix_len;

	if (!src || !prefix)
		return (NULL);
	src_len = ft_strlen(src);
	prefix_len = ft_strlen(prefix);
	new_str = malloc((src_len + prefix_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	tmp_strcpy(new_str, prefix, prefix_len);
	tmp_strcpy(new_str + prefix_len, src, src_len);
	new_str[src_len + prefix_len] = '\0';
	if (free_src)
		free(src);
	return (new_str);
}

char	*ft_str_addsufix(char *src, char *sufix, int free_src)
{
	char	*new_str;
	size_t	src_len;
	size_t	sufix_len;

	if (!src || !sufix)
		return (NULL);
	src_len = ft_strlen(src);
	sufix_len = ft_strlen(sufix);
	new_str = malloc((src_len + sufix_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	tmp_strcpy(new_str, src, src_len);
	tmp_strcpy(new_str + src_len, sufix, sufix_len);
	new_str[src_len + sufix_len] = '\0';
	if (free_src)
		free(src);
	return (new_str);
}

static void	tmp_strcpy(char *target, char *src, size_t size)
{
	size_t	i;

	if (!target || !src)
		return ;
	i = 0;
	while (i < size)
	{
		target[i] = src[i];
		i++;
	}
}
