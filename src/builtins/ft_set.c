/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:52:24 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/12 11:18:59 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_set(t_linkedlist_array *ht_env, char *key_value)
{
	t_ht *item;
	t_env_value	*value;

	item = ft_content_node_ht(key_value);
	value = (t_env_value *)item->value;
	value->set = 1;
	ft_include_item_ht(ht_env, item, ft_free_item_ht_env);
}
