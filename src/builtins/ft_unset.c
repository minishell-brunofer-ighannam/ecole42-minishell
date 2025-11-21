/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:39:10 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/21 12:03:30 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(t_linkedlist_array *ht_env, const char *key)
{
	t_linkedlist_node *found;
	t_ht *remove;

	if (!key || !ht_env)
		return ;
	found = (t_linkedlist_node *)ft_find_ht(ht_env, key);
	if (!found)
		return ;
	remove = (t_ht *)found->content;
	ft_remove_item_ht(ht_env, remove, ft_free_item_ht_env);
}
