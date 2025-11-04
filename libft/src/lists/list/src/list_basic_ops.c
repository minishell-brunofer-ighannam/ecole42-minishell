/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_basic_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:12:59 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/21 12:14:29 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list_node	*list_detach_node(t_list *self, t_list_node *node)
{
	if (!self || !node)
		return (NULL);
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (self->head == node)
		self->head = node->next;
	if (self->tail == node)
		self->tail = node->prev;
	self->length--;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	list_push(t_list *self, t_list_node *node)
{
	if (!self || !node)
		return (0);
	node->next = NULL;
	node->prev = self->tail;
	self->tail->next = node;
	self->length++;
	return (1);
}

int	list_push_head(t_list *self, t_list_node *node)
{
	if (!self || node)
		return (0);
	node->next = self->head;
	node->prev = NULL;
	self->head = node;
	self->length++;
	return (1);
}

t_list_node	*list_index(t_list *self, int idx)
{
	t_list_node	node;
	int			start;

	if (!self || !self->length || idx >= self->length)
		return (NULL);
	start = 0;
	while (idx--)
	{
		idx--;
	}
}
