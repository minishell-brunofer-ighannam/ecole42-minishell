/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:39:10 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/09 16:01:26 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_env **env, char *key)
{
	t_env			*entry;
	t_env			*prev;
	unsigned long	index;

	index = ft_hash(key);
	entry = env[index];
	prev = NULL;
	while (entry)
	{
		if (ft_strncmp(entry->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = entry->next;
			else
				env[index] = entry->next;
			free(entry->key);
			free(entry->value);
			free(entry);
			return ;
		}
		prev = entry;
		entry = entry->next;
	}
}
