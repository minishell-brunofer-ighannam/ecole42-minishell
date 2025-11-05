/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:29:53 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/05 20:17:57 by ighannam         ###   ########.fr       */
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
			if (value)
			{
				free(entry->value);
				entry->value = ft_strdup(value);
			}
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

void ft_remove_ht(t_env **env, char *key)
{
	t_env	*entry;
	t_env	*prev;
	unsigned long index;

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

char *ft_find_env_value(char *key, t_env **env)
{
	t_env *found;
	unsigned long index;

	if (!key || !env)
		return (NULL);
	index = ft_hash(key);
	found = env[index];
	while (found)
	{
		if (ft_strncmp(key, found->key, ft_strlen(key) + 1) == 0)
			return (found->value);
		found = found->next;
	}
	return (NULL);
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
				if (entry->value)
					printf("%s=%s\n", entry->key, entry->value);
				entry = entry->next;
			}
		}
		i++;
	}
}

void	ft_export(t_env **env, char *key, char *value)
{
	int i;
	int j;

	if (!key)
	{
		i = 0;
		while (i < ENV_HASH_SIZE - 1)
		{
			j = i + 1;
			while (j < )
			{
				/* code */
			}
			
		}
		
		
		return ;
	}
	ft_include_ht(env, key, value);
}

int	main(int argc, char **argv, char **envp)
{
	t_env **env;
	(void)argc;
	(void)argv;
	env = ft_init_ht(envp);
	//ft_env(env);
	printf("%s\n", ft_find_env_value("PATH", env));
	return (0);
}