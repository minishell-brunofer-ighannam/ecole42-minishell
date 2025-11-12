/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:38:13 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/11 18:10:58 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_print_node_env(void *node);

void	ft_env(t_linkedlist_array *ht_env)
{
	ht_env->iteri(ht_env, ft_print_node_env);
}

static void	ft_print_node_env(void *node)
{
	t_ht				*content;
	t_env_value			*env_value;
	t_linkedlist_node	*n;

	n = (t_linkedlist_node *)node;
	if (n)
	{
		content = (t_ht *)n->content;
		env_value = (t_env_value *)content->value;
		if (content && content->key && ft_strncmp(content->key, "_",
				ft_strlen(content->key)) != 0 && env_value->set == 0
			&& env_value->value)
			printf("%s=%s\n", content->key, env_value->value);
		else if (content && content->key && ft_strncmp(content->key, "_",
				ft_strlen(content->key)) != 0 && env_value->set == 0
			&& env_value->value == NULL)
			return ;
		else if (content && content->key && ft_strncmp(content->key, "_",
				ft_strlen(content->key)) != 0 && env_value->set == 0
			&& *(env_value->value) == 0)
			printf("%s=\n", content->key);
		else if (content && content->key && ft_strncmp(content->key, "_",
				ft_strlen(content->key)) == 0)
			printf("_=/usr/bin/env\n");
	}
}

// void	ft_env(t_linkedlist_array *ht_env)
// {
// 	int		i;
// 	t_linkedlist	*entry;

// 	if (!ht_env)
// 		return ;
// 	i = 0;
// 	while (i < ENV_HASH_SIZE)
// 	{
// 		if (ht_env->list[i]->first)
// 		{
// 			entry = ht_env[i];
// 			while (entry)
// 			{
// 				if (entry->value && entry->set == 0 && ft_strncmp(entry->key,
// 						"_", ft_strlen(entry->key) + 1) != 0)
// 					printf("%s=%s\n", entry->key, entry->value);
// 				else if (entry->value && ft_strncmp(entry->key, "_",
// 						ft_strlen(entry->key) + 1) == 0)
// 					printf("_=/usr/bin/env\n");
// 				entry = entry->next;
// 			}
// 		}
// 		i++;
// 	}
// }
