/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:40:29 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/09 16:01:12 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_keys_array_export(t_env **env);
static int	ft_count_keys_export(t_env **env);
static void	ft_ordene_keys(char **all_keys);
static void	ft_swap_keys(int i, int j, char **all_keys);

void	ft_export(t_env **env, char *key, char *value)
{
	int		i;
	char	**keys_set;
	int		count;

	count = ft_count_keys_export(env);
	if (!key)
	{
		keys_set = ft_keys_array_export(env);
		ft_ordene_keys(keys_set);
		i = -1;
		while (++i < count)
		{
			if (keys_set[i])
			{
				if (ft_find_env_value(keys_set[i], env))
					printf("declare -x %s=\"%s\"\n", keys_set[i],
						ft_find_env_value(keys_set[i], env));
				else
					printf("declare -x %s\n", keys_set[i]);
			}
		}
		free(keys_set);
		return ;
	}
	ft_set(env, key, value, 0);
}

static int	ft_count_keys_export(t_env **env)
{
	int		count;
	int		i;
	t_env	*entry;

	count = 0;
	i = 0;
	while (i < ENV_HASH_SIZE)
	{
		if (env[i])
		{
			entry = env[i];
			while (entry)
			{
				if (entry->set == 0 && ft_strncmp(entry->key, "_",
						ft_strlen(entry->key) + 1))
					count++;
				entry = entry->next;
			}
		}
		i++;
	}
	return (count);
}

static char	**ft_keys_array_export(t_env **env)
{
	char	**all_keys;
	int		i;
	int		j;
	t_env	*entry;

	all_keys = ft_calloc(ft_count_keys_export(env) + 1, sizeof(char *));
	i = -1;
	j = -1;
	while (++i < ENV_HASH_SIZE)
	{
		if (env[i])
		{
			entry = env[i];
			while (entry)
			{
				if (entry->set == 0 && ft_strncmp(entry->key, "_",
						ft_strlen(entry->key) + 1))
					all_keys[++j] = entry->key;
				entry = entry->next;
			}
		}
	}
	return (all_keys);
}

static void	ft_ordene_keys(char **all_keys)
{
	int	i;
	int	j;

	i = -1;
	while (all_keys[++i])
	{
		j = i;
		while (all_keys[++j])
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

static void	ft_swap_keys(int i, int j, char **all_keys)
{
	char	*temp;

	temp = all_keys[i];
	all_keys[i] = all_keys[j];
	all_keys[j] = temp;
}
