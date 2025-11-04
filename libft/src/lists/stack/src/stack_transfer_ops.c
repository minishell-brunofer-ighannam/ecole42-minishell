/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_transfer_ops.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:04:52 by valero            #+#    #+#             */
/*   Updated: 2025/08/21 12:12:21 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int	stack_push(t_stack *self, t_stack_node *node)
{
	if (!self || !node)
		return (0);
	node->next = NULL;
	node->prev = self->top;
	if (!self->length)
		self->bottom = node;
	else
		self->top->next = node;
	self->top = node;
	self->length++;
	return (1);
}

int	stack_push_unique(t_stack *self, t_stack_node *node,
		int (*is_equal)(void *self_content, void *content))
{
	if (self->includes(self, node->content, is_equal))
		return (0);
	return (self->push(self, node));
}

t_stack_node	*stack_pop(t_stack *self)
{
	t_stack_node	*popped_node;

	if (!self || !self->top)
		return (NULL);
	popped_node = self->detach_node(self, self->top);
	if (!popped_node)
		return (NULL);
	return (popped_node);
}

int	stack_transfer_top(t_stack *self, t_stack *other_stack)
{
	t_stack_node	*transfered_node;
	int				push_succeeded;

	transfered_node = NULL;
	if (!self || !other_stack || !self->length)
		return (0);
	transfered_node = self->pop(self);
	if (!transfered_node)
		return (0);
	push_succeeded = other_stack->push(other_stack, transfered_node);
	if (!push_succeeded)
		self->push(self, transfered_node);
	return (push_succeeded);
}
