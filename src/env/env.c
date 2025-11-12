/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:25:06 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/12 15:58:50 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_linkedlist_array	*ft_init_ht_env(char **envp)
{
	t_linkedlist_array	*ht_env;

	ht_env = ft_new_linkedlist_array(ENV_HASH_SIZE);
	if (!envp)
		return (ht_env);
	while (*envp)
	{
		ft_include_item_ht(ht_env, ft_content_node_ht(*envp),
			ft_free_item_ht_env);
		envp++;
	}
	return (ht_env);
}

void	ft_split_key_value(char *s, char **key_value)
{
	int		len;
	char	*key;
	char	*value;
	int		i;

	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	key = ft_calloc(len + 1, sizeof(char));
	i = -1;
	while (s[++i] && s[i] != '=')
		key[i] = s[i];
	i++;
	if (ft_strlen(s) - len == 0)
		value = NULL;
	else
	{
		value = ft_calloc(ft_strlen(s) - len + 1, sizeof(char));
		len = 0;
		while (s[i])
			value[len++] = s[i++];
	}
	key_value[0] = key;
	key_value[1] = value;
}

t_ht	*ft_content_node_ht(char *s)
{
	t_ht		*content;
	t_env_value	*value;
	char		**key_value;

	key_value = ft_calloc(2, sizeof(char *));
	ft_split_key_value(s, key_value);
	content = malloc(sizeof(t_ht));
	value = malloc(sizeof(t_env_value));
	content->key = key_value[0];
	value->set = 0;
	value->value = key_value[1];
	content->value = value;
	free(key_value);
	return (content);
}

void	ft_free_item_ht_env(void *node_ht)
{
	t_ht		*node_to_free;
	t_env_value	*value_to_free;

	node_to_free = (t_ht *)node_ht;
	value_to_free = (t_env_value *)node_to_free->value;
	free(node_to_free->key);
	free(value_to_free->value);
	free(node_to_free->value);
	free(node_to_free);
}
