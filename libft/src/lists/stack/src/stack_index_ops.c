/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_index_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:36:13 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/17 20:10:26 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int	stack_includes(t_stack *self, void *content,
		int (*is_equal)(void *self_content, void *content))
{
	int				end;
	int				start;
	t_stack_node	*top;
	t_stack_node	*bottom;

	if (!self->length)
		return (0);
	top = self->top;
	bottom = self->bottom;
	end = self->length - 1;
	start = 0;
	while (start <= end)
	{
		if (is_equal(top->content, content))
			return (1);
		if (top != bottom && is_equal(bottom->content, content))
			return (1);
		if (top->prev)
			top = top->prev;
		if (bottom->next)
			bottom = bottom->next;
		end--;
		start++;
	}
	return (0);
}
