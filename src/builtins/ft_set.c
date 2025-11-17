/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:52:24 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/17 02:22:37 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_set(t_linkedlist_array *ht_env, char *key_value)
{
	t_ht				*item;
	t_env_value			*value;
	t_linkedlist_node	*found;

	item = ft_content_node_ht(key_value);
	value = (t_env_value *)item->value;
	found = ft_find_ht(ht_env, item->key);
	if (!found || !(found->content)
		|| ((t_env_value *)((t_ht *)(found->content))->value)->set == 1)
		value->set = 1;
	else
		value->set = 0;
	ft_include_item_ht(ht_env, item, ft_free_item_ht_env);
}
