/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:01:40 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/14 18:56:17 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				if (ft_strncmp(list[i], list[j],
						ft_strlen(list[i])) > 0)
					ft_swap_array_str(i, j, list);
			}
		}
	}
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
	int i;

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
