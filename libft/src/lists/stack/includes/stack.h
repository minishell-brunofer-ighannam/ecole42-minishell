/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:35:01 by brunofer          #+#    #+#             */
/*   Updated: 2025/08/13 14:26:51 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

typedef struct s_stack_node
{
	void				*content;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}	t_stack_node;

typedef struct s_stack
{
	unsigned int	length;
	t_stack_node	*bottom;
	t_stack_node	*top;
	t_stack_node	*(*create_node)(void *content);
	int				(*swap_first_node)(struct s_stack *self);
	int				(*rotate)(struct s_stack *self, int reverse);
	int				(*push)(struct s_stack *self, t_stack_node *node);
	t_stack_node	*(*pop)(struct s_stack *self);
	int				(*transfer_top)(struct s_stack *self,
			struct s_stack *other_stack);
	int				(*destroy)(struct s_stack **self_ref,
			void (*del_node_content)(void *content));
	t_stack_node	*(*detach_node)(struct s_stack *self, t_stack_node *node);
	int				(*includes)(struct s_stack *self, void *content,
			int (*is_equal)(void *self_content, void *content));
	int				(*push_unique)(struct s_stack *self, t_stack_node *node,
			int (*is_equal)(void *self_content, void *content));
}	t_stack;

t_stack			*new_stack(void);
t_stack_node	*stack_new_node(void *content);
void			*stack_delete_node(t_stack_node **node_ref,
					void (*del_node_content)(void *content));
int				stack_swap_first_node(t_stack *self);
int				stack_rotate(t_stack *self, int reverse);
int				stack_push(t_stack *self, t_stack_node *node);
t_stack_node	*stack_pop(t_stack *self);
int				stack_transfer_top(t_stack *self, t_stack *other_stack);
int				stack_destroy(t_stack **self_ref,
					void (*del_node_content)(void *content));
t_stack_node	*stack_detach_node(t_stack *self, t_stack_node *node);
int				stack_includes(t_stack *self, void *content,
					int (*is_equal)(void *self_content, void *content));
int				stack_push_unique(t_stack *self, t_stack_node *node,
					int (*is_equal)(void *self_content, void *content));

#endif
