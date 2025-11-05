/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:29:53 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/05 19:10:11 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

int	ft_hash(char *key)
{
	unsigned long	hash;

	if (!key)
		return (-1);
	hash = 5381;
	while (*key)
	{
		hash = ((hash << 5) + hash) + *key;
		key++;
	}
	return (hash % ENV_HASH_SIZE);
}

void	ft_include_ht(t_env **env, char *key, char *value)
{
	t_env	*entry;
	t_env	*new_entry;

	entry = env[ft_hash(key)];
	while (entry)
	{
		if (ft_strncmp(entry->key, key, ft_strlen(key) + 1) == 0)
		{
			free(entry->value);
			entry->value = ft_strdup(value);
			return ;
		}
		entry = entry->next;
	}
	new_entry = malloc(sizeof(t_env));
	new_entry->key = ft_strdup(key);
	new_entry->value = ft_strdup(value);
	new_entry->next = env[ft_hash(key)];
	env[ft_hash(key)] = new_entry;
}

t_env	**ft_init_ht(char **envp)
{
	t_env	**env;
	char	**key_value;

	if (!envp)
		return (NULL);
	env = ft_calloc(ENV_HASH_SIZE, sizeof(t_env *));
	if (!env)
		return (NULL);
	while (*envp)
	{
		key_value = ft_split(*envp, '=');
		if (key_value && key_value[0])
		{
			if (key_value[1])
				ft_include_ht(env, key_value[0], key_value[1]);
			else
				ft_include_ht(env, key_value[0], "");
			free(key_value[0]);
			if (key_value[1])
				free(key_value[1]);
			free(key_value);
		}
		envp++;
	}
	return (env);
}

void	ft_env(t_env **env)
{
	int		i;
	t_env	*entry;

	if (!env)
		return ;
	i = 0;
	while (i < ENV_HASH_SIZE)
	{
		if (env[i])
		{
			entry = env[i];
			while (entry)
			{
				printf("%s=%s\n", entry->key, entry->value);
				entry = entry->next;
			}
		}
		i++;
	}
	
}

int	main(int argc, char **argv, char **envp)
{
	t_env **env;
	(void)argc;
	(void)argv;
	env = ft_init_ht(envp);
	ft_env(env);
	return (0);
}