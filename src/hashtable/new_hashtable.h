/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_hashtable.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:15:08 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/11 11:17:37 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_HASHTABLE_H
#define NEW_HASHTABLE_H

#include "../includes/minishell.h"

typedef struct s_ht
{
	char			*key;
	void			*value;
}					t_ht;

int	ft_hash(char *key);
t_linkedlist_array *ft_init_ht(int size, t_ht **key_value);
void ft_free_item_ht(void *node_ht);
void *ft_find_ht(t_linkedlist_array *ht ,char *key);
void ft_include_item_ht(t_linkedlist_array *ht, t_ht *new);
void ft_remove_item_ht(t_linkedlist_array *ht, t_ht *new);

#endif