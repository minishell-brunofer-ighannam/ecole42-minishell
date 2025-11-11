/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:29:53 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/11 11:03:55 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "../includes/minishell.h"

// void	ft_set(t_env **env, char *key, char *value, int set)
// {
// 	t_env	*entry;
// 	t_env	*new_entry;

// 	entry = env[ft_hash(key)];
// 	while (entry)
// 	{
// 		if (ft_strncmp(entry->key, key, ft_strlen(key) + 1) == 0)
// 		{
// 			if (value)
// 			{
// 				free(entry->value);
// 				entry->value = ft_strdup(value);
// 				if (entry->set == 0)
// 					entry->set = set;
// 			}
// 			return ;
// 		}
// 		entry = entry->next;
// 	}
// 	new_entry = malloc(sizeof(t_env));
// 	new_entry->key = ft_strdup(key);
// 	new_entry->value = ft_strdup(value);
// 	new_entry->set = set;
// 	new_entry->next = env[ft_hash(key)];
// 	env[ft_hash(key)] = new_entry;
// }

// t_env	**ft_init_ht(char **envp)
// {
// 	t_env	**env;
// 	char	**key_value;

// 	if (!envp)
// 		return (NULL);
// 	env = ft_calloc(ENV_HASH_SIZE, sizeof(t_env *));
// 	if (!env)
// 		return (NULL);
// 	while (*envp)
// 	{
// 		key_value = ft_split_env(*envp);
// 		if (key_value && key_value[0])
// 		{
// 			if (key_value[1])
// 				ft_set(env, key_value[0], key_value[1], 0);
// 			else
// 				ft_set(env, key_value[0], "", 0);
// 			free(key_value[0]);
// 			if (key_value[1])
// 				free(key_value[1]);
// 			free(key_value);
// 		}
// 		envp++;
// 	}
// 	return (env);
// }


// char	*ft_find_env_value(char *key, t_env **env)
// {
// 	t_env			*found;
// 	unsigned long	index;

// 	if (!key || !env)
// 		return (NULL);
// 	index = ft_hash(key);
// 	found = env[index];
// 	while (found)
// 	{
// 		if (ft_strncmp(key, found->key, ft_strlen(key) + 1) == 0)
// 			return (found->value);
// 		found = found->next;
// 	}
// 	return (NULL);
// }
