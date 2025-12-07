/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:01:40 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/07 20:16:21 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_strcasecmp(const char *s1, const char *s2);

void	ft_ordene_array_str(char **list)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	while (list[size])
		size++;
	i = -1;
	while (++i < size - 1)
	{
		j = i;
		while (++j < size)
		{
			if (list[i] && list[j])
			{
				if (ft_strcmp(list[i], list[j]) > 0)
					ft_swap_array_str(i, j, list);
			}
		}
	}
}

void	ft_ordene_array_str_alpha(char **list)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	while (list[size])
		size++;
	i = -1;
	while (++i < size - 1)
	{
		j = i;
		while (++j < size)
		{
			if (list[i] && list[j])
			{
				if (ft_strcasecmp(list[i], list[j]) > 0)
					ft_swap_array_str(i, j, list);
			}
		}
	}
}

static int	ft_strcasecmp(const char *s1, const char *s2)
{
	int		i;
	char	c1;
	char	c2;

	i = 0;
	while (s1[i] && s2[i])
	{
		c1 = ft_tolower(s1[i]);
		c2 = ft_tolower(s2[i]);
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
}

void	ft_swap_array_str(int i, int j, char **list)
{
	char	*temp;

	temp = list[i];
	list[i] = list[j];
	list[j] = temp;
}

void	ft_clean_array_str(char **list)
{
	int	i;

	if (!list)
		return ;
	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list[i]);
	free(list);
}
