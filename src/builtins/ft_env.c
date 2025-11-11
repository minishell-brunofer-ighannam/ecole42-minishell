// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_env.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/11/09 15:38:13 by ighannam          #+#    #+#             */
// /*   Updated: 2025/11/10 19:08:31 by ighannam         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

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
