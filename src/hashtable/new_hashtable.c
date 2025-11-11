// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   new_hashtable.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/11/10 10:33:35 by ighannam          #+#    #+#             */
// /*   Updated: 2025/11/10 18:59:08 by ighannam         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// int	ft_hash(char *key)
// {
// 	unsigned long	hash;

// 	if (!key)
// 		return (-1);
// 	hash = 5381;
// 	while (*key)
// 	{
// 		hash = ((hash << 5) + hash) + *key;
// 		key++;
// 	}
// 	return (hash % ENV_HASH_SIZE);
// }

// t_linkedlist_array *ft_init_ht(int size, t_ht **key_value)
// {
// 	t_linkedlist_array *ht;
// 	int i;

// 	ht = ft_new_linkedlist_array(size);
// 	if (!ht)
// 		return (NULL);
// 	i = 0;
// 	while (key_value[i])
// 	{
// 		if (!(ht->push(ht, ft_hash(key_value[i]->key), key_value[i]->value)))
// 		{
// 			ht->destroy(&ht, ft_free_item_ht);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (ht);
// }

// void ft_free_item_ht(void *node_ht)
// {
// 	t_ht *node_to_free;
// 	node_to_free = (t_ht *)node_ht;

// 	free(node_to_free->key);
// 	free(node_to_free->value);
// 	free(node_to_free);
// }

// void *ft_find_ht(t_linkedlist_array *ht ,char *key)
// {
// 	char *value;
// 	t_linkedlist *entry;
// 	t_ht	*key_value;
// 	t_linkedlist_node *curr_node;
// 	int hash;

// 	hash = ft_hash(key);
// 	if (hash > ht->size)
// 		return (NULL);
// 	entry = ht->list[ft_hash(key)];
// 	curr_node = entry->first;
// 	while (curr_node)
// 	{
// 		key_value = (t_ht *)curr_node->content;
// 		if (ft_strncmp(key, key_value->key, ft_strlen(key)) == 0)
// 			return (key_value);
// 		curr_node = curr_node->next;
// 	}
// 	return (NULL);
// }

// void ft_include_item_ht(t_linkedlist_array *ht, t_ht *new)
// {
// 	t_ht *found;
// 	t_linkedlist *list;

// 	found = ft_find_ht(ht, new->key);
// 	if (found)
// 	{
// 		list = ht->list[ft_hash(found->key)];
// 		list->remove(list, found, ft_free_item_ht);
// 		list->push(list, new);
// 		return ;
// 	}
// 	ht->push(ht, ft_hash(new->key), new);
// }


// void ft_remove_item_ht(t_linkedlist_array *ht, t_ht *new)
// {
// 	t_ht *found;
// 	t_linkedlist *list;

// 	found = ft_find_ht(ht, new->key);
// 	if (found)
// 	{
// 		list = ht->list[ft_hash(found->key)];
// 		list->remove(list, found, ft_free_item_ht);
// 	}
// }
