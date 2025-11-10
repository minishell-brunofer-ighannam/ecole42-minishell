/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:25:06 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/10 19:15:18 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_linkedlist_array *ft_init_ht_env(char **envp)
{
	t_linkedlist_array *ht_env;

	ht_env = ft_new_linkedlist_array(ENV_HASH_SIZE);
	while (*envp)
	{
		ft_include_item_ht(ht_env, ft_split_env_(*envp));
		envp++;
	}
	return (ht_env);
}

t_ht	*ft_split_env_(char *s)
{
	t_ht	*key_value;
	t_env_value	*content;
	int		len;
	char	*key;
	char	*value;
	int		i;

	len = 0;
	key_value = ft_calloc(1, sizeof(t_ht *));
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
	content = ft_calloc(1, sizeof(t_env_value *));
	content->set = 0;
	content->value = value;
	key_value->key = key;
	key_value->value = content;
	return (key_value);
}
