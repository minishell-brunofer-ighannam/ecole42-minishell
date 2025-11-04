/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:00:35 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/17 19:10:35 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*new_list(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	list->length = 0;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

t_list_node	*list_new_node(void *content)
{
	t_list_node	*node;

	node = (t_list_node *)malloc(sizeof(t_list_node));
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
