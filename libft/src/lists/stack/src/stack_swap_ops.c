/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_swap_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:04:52 by valero            #+#    #+#             */
/*   Updated: 2025/08/21 16:43:42 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int	stack_swap_first_node(t_stack *self)
{
	t_stack_node	*swapped_node;

	if (!self || self->length < 2)
		return (0);
	swapped_node = self->detach_node(self, self->top->prev);
	if (!swapped_node)
		return (0);
	self->push(self, swapped_node);
	return (1);
}

int	stack_rotate(t_stack *self, int reverse)
{
	t_stack_node	*rotated_node;

	if (!self || self->length < 2)
		return (0);
	if (!reverse)
	{
		rotated_node = self->detach_node(self, self->top);
		if (!rotated_node)
			return (0);
		rotated_node->next = self->bottom;
		self->bottom->prev = rotated_node;
		self->bottom = rotated_node;
		self->length++;
		return (1);
	}
	rotated_node = self->detach_node(self, self->bottom);
	if (!rotated_node)
		return (0);
	self->push(self, rotated_node);
	return (1);
}

t_stack_node	*stack_detach_node(t_stack *self, t_stack_node *node)
{
	if (!self || !node)
		return (NULL);
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (self->top == node)
		self->top = node->prev;
	if (self->bottom == node)
		self->bottom = node->next;
	self->length--;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
