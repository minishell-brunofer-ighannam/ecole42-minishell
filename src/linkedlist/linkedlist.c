/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:52:21 by valero            #+#    #+#             */
/*   Updated: 2025/11/06 17:13:29 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linkedlist.h"

static void	*ft_linkedlist_destroy(
				t_linkedlist	*self, void (*free_content)(void *arg));
static void	ft_push_new_node(t_linkedlist	*self, void *content);

t_linkedlist	*ft_new_linkedlist(void)
{
	t_linkedlist	*linkedlist;

	linkedlist = ft_calloc(1, sizeof(t_linkedlist));
	if (!linkedlist)
		return (NULL);
	linkedlist->self_ref = &linkedlist;
	linkedlist->push = ft_push_new_node;
	linkedlist->destroy = ft_linkedlist_destroy;
}

static void	ft_push_new_node(t_linkedlist	*self, void *content)
{
	t_linkedlist_node	*node;

	node = ft_new_node(content);
	if (!node)
		return ;
	self->size++;
	if (self->size == 1)
	{
		self->first = node;
		self->last = node;
		return ;
	}
	node->prev = self->last;
	self->last->next = node;
	self->last = node;
}


static void	*ft_linkedlist_destroy(
				t_linkedlist	*self, void (*free_content)(void *arg))
{
	t_linkedlist		**self_ref;
	t_linkedlist_node	*curr_node;
	t_linkedlist_node	*next_node;

	if (!self)
		return (NULL);
	if (self->size)
	{
		self_ref = self->self_ref;
		curr_node = self->first;
		next_node = curr_node->next;
		while (curr_node)
		{
			curr_node->destroy(curr_node, free_content);
			curr_node = next_node;
			if (curr_node)
				next_node = curr_node->next;
		}
	}
	free(self);
	*self_ref = NULL;
}
