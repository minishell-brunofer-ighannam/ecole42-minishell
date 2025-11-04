/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:06:57 by valero            #+#    #+#             */
/*   Updated: 2025/09/02 16:03:34 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack	*new_stack(void)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	stack->length = 0;
	stack->bottom = NULL;
	stack->top = NULL;
	stack->create_node = stack_new_node;
	stack->swap_first_node = stack_swap_first_node;
	stack->rotate = stack_rotate;
	stack->push = stack_push;
	stack->pop = stack_pop;
	stack->transfer_top = stack_transfer_top;
	stack->destroy = stack_destroy;
	stack->detach_node = stack_detach_node;
	stack->includes = stack_includes;
	stack->push_unique = stack_push_unique;
	return (stack);
}

t_stack_node	*stack_new_node(void *content)
{
	t_stack_node	*new_node;

	new_node = (t_stack_node *)malloc(sizeof(t_stack_node));
	new_node->content = content;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	*stack_delete_node(t_stack_node **node_ref,
		void (*del_node_content)(void *content))
{
	if (!node_ref || !*node_ref)
		return (NULL);
	del_node_content(&(*node_ref)->content);
	free(*node_ref);
	*node_ref = NULL;
	return (NULL);
}

int	stack_destroy(t_stack **self_ref, void (*del_node_content)(void *content))
{
	t_stack			*self;
	t_stack_node	*popped_node;

	self = *self_ref;
	if (!self_ref || !self)
		return (0);
	while (self->length)
	{
		popped_node = self->pop(self);
		stack_delete_node(&popped_node, del_node_content);
	}
	free(self);
	self = NULL;
	return (1);
}
