/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:11:25 by valero            #+#    #+#             */
/*   Updated: 2025/08/21 12:11:49 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "stack.h"
// #include <stdio.h>

// void	del_node_content(void *content)
// {
// 	content = NULL;
// }

// void	print_stack(t_stack *self)
// {
// 	t_stack_node	*stack;
// 	int				idx;

// 	stack = self->top;
// 	idx = 0;
// 	printf("item %d = %d\n", idx, *(int *)stack->content);
// 	printf("self->top = %p\n", self->top);
// 	printf("self->top->prev = %p\n", self->top->prev->prev);
// 	while (stack)
// 	{
// 		printf("item %d = %d\n", idx, *(int *)stack->content);
// 		stack = stack->prev;
// 		idx++;
// 	}
// }

// int	is_equal(void *self_content, void *content)
// {
// 	return (*(int *)self_content == *(int *)content);
// }

// t_stack_node	*make_stack(t_stack *stack, int nbrs[20], int idx)
// {
// 	return (stack->create_node(&(nbrs[idx])));
// }

// int	main(void)
// {
// 	t_stack	*stack;
// 	t_stack	*stack2;

// 	stack = new_stack();
// 	stack2 = new_stack();
// 	int	nbrs[20] = {0, 1, 2, 3, 4, 5, 6 ,7 ,8, 9, 10, 11, 12, 13, 14, 15};

// 	stack->push(stack, make_stack(stack, nbrs, 3));
// 	stack->push(stack, make_stack(stack, nbrs, 2));
// 	stack->push(stack, make_stack(stack, nbrs, 2));
// 	stack->push_unique(stack, make_stack(stack, nbrs, 3), is_equal);
// 	stack->push(stack, make_stack(stack, nbrs, 2));
// 	stack->push(stack, make_stack(stack, nbrs, 3));
// 	stack->push(stack, make_stack(stack, nbrs, 3));
// 	stack->push(stack, make_stack(stack, nbrs, 9));
// 	stack->push_unique(stack, make_stack(stack, nbrs, 3), is_equal);
// 	stack->push_unique(stack, make_stack(stack, nbrs, 9), is_equal);

// 	print_stack(stack);

// 	int includes = stack->includes(stack, &nbrs[8], is_equal);
// 	printf("stack includes 8 = %d\n", includes);
// 	includes = stack->includes(stack, &(nbrs[2]), is_equal);
// 	printf("stack includes 2 = %d\n", includes);

// 	stack->transfer_top(stack, stack2);
// 	stack->transfer_top(stack, stack2);
// 	stack->transfer_top(stack, stack2);
// 	// stack->rotate(&stack, 1);
// 	// ------------------------------------
// 	t_stack_node *current;
// 	current = stack2->pop(stack2);
// 	printf("pointer = %p, data = %d\n",
	// current->content, *(int *)current->content);
// 	stack->push(stack, current);
// 	// ------------------------------------
// 	current = stack2->pop(stack2);
// 	printf("pointer = %p, data = %d\n",
	// current->content, *(int *)current->content);
// 	stack->push(stack, current);
// 	// ------------------------------------
// 	current = stack2->pop(stack2);
// 	printf("pointer = %p, data = %d\n",
	// current->content, *(int *)current->content);
// 	stack->push(stack, current);
// 	stack->destroy(&stack, del_node_content);
// 	stack2->destroy(&stack2, del_node_content);
// }
