/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:29:53 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/06 11:51:07 by ighannam         ###   ########.fr       */
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

void	ft_set(t_env **env, char *key, char *value, int set)
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
				if (entry->set == 0)
					entry->set = set;
			}
			return ;
		}
		entry = entry->next;
	}
	new_entry = malloc(sizeof(t_env));
	new_entry->key = ft_strdup(key);
	new_entry->value = ft_strdup(value);
	new_entry->set = set;
	new_entry->next = env[ft_hash(key)];
	env[ft_hash(key)] = new_entry;
}

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
		key_value = ft_split_env(*envp);
		if (key_value && key_value[0])
		{
			if (key_value[1])
				ft_set(env, key_value[0], key_value[1], 0);
			else
				ft_set(env, key_value[0], "", 0);
			free(key_value[0]);
			if (key_value[1])
				free(key_value[1]);
			free(key_value);
		}
		envp++;
	}
	return (env);
}

char	**ft_split_env(char *s)
{
	char	**key_value;
	int		len;
	char	*key;
	char	*value;
	int		i;

	len = 0;
	key_value = ft_calloc(3, sizeof(char *));
	while (s[len] && s[len] != '=')
		len++;
	key = ft_calloc(len + 1, sizeof(char));
	i = -1;
	while (s[++i] && s[i] != '=')
		key[i] = s[i];
	i++;
	value = ft_calloc(ft_strlen(s) - len + 1, sizeof(char));
	len = 0;
	while (s[i])
		value[len++] = s[i++];
	key_value[0] = key;
	key_value[1] = value;
	return (key_value);
}

char	*ft_find_env_value(char *key, t_env **env)
{
	t_env			*found;
	unsigned long	index;

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
				if (entry->value && entry->set == 0 && ft_strncmp(entry->key,
						"_", ft_strlen(entry->key) + 1) != 0)
					printf("%s=%s\n", entry->key, entry->value);
				else if (entry->value && ft_strncmp(entry->key,
						"_", ft_strlen(entry->key) + 1) == 0)
					printf("_=/usr/bin/env\n");
				entry = entry->next;
			}
		}
		i++;
	}
}

void	ft_export(t_env **env, char *key, char *value)
{
	int		i;
	char	**all_keys;

	if (!key)
	{
		all_keys = ft_calloc(ENV_HASH_SIZE, sizeof(char *));
		ft_ordene_keys(env, all_keys);
		i = -1;
		while (++i < ENV_HASH_SIZE)
		{
			if (all_keys[i])
			{
				if (ft_find_env_value(all_keys[i], env)) //Ajustar para set = 1 e _=
					printf("declare -x %s=\"%s\"\n", all_keys[i],
						ft_find_env_value(all_keys[i], env));
				else
					printf("declare -x %s\n", all_keys[i]);
			}
		}
		free(all_keys);
		return ;
	}
	ft_set(env, key, value, 0);
}

void	ft_ordene_keys(t_env **env, char **all_keys)
{
	int	i;
	int	j;

	i = -1;
	while (++i < ENV_HASH_SIZE)
	{
		if (env[i])
			all_keys[i] = env[i]->key;
	}
	i = -1;
	while (++i < ENV_HASH_SIZE - 1)
	{
		j = i;
		while (++j < ENV_HASH_SIZE)
		{
			if (all_keys[i] && all_keys[j])
			{
				if (ft_strncmp(all_keys[i], all_keys[j],
						ft_strlen(all_keys[i])) > 0)
					ft_swap_keys(i, j, all_keys);
			}
		}
	}
}

void	ft_swap_keys(int i, int j, char **all_keys)
{
	char	*temp;

	temp = all_keys[i];
	all_keys[i] = all_keys[j];
	all_keys[j] = temp;
}

char	*ft_find_path(t_env **env, char *cmd)
{
	int		i;
	char	*path;
	char	*path_temp;
	char	**possible_paths;

	possible_paths = ft_split(ft_find_env_value("PATH", env), ':');
	i = -1;
	if (!possible_paths || ft_strlen(cmd) == 0)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	while (possible_paths[++i])
	{
		path = ft_strjoin(possible_paths[i], "/");
		path_temp = path;
		path = ft_strjoin(path, cmd);
		free(path_temp);
		if (access(path, X_OK) == 0)
			return (path);
		else
			free(path);
	}
	printf("command not found: %s\n", cmd);
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_env **env;
	(void)argc;
	(void)argv;
	env = ft_init_ht(envp);
	//ft_env(env);
	// printf("%s\n", ft_find_env_value("DBUS_STARTER_ADDRESS", env));
	ft_export(env, NULL, NULL);
	//printf("path: %s\n", ft_find_path(env, "wc"));
	return (0);
}