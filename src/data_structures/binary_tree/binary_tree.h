/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:23:55 by valero            #+#    #+#             */
/*   Updated: 2025/11/26 19:09:19 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include <stdbool.h>

typedef struct s_binary_tree_node	t_binary_tree_node;
struct s_binary_tree_node
{
	t_binary_tree_node	*parent;
	t_binary_tree_node	*left;
	t_binary_tree_node	*right;
	int					node_depth;
	void				*content;
	void				*(*destroy)(t_binary_tree_node **self_ref,
			void (*free_content)(void *arg));
};

typedef struct s_binary_tree		t_binary_tree;
struct s_binary_tree
{
	t_binary_tree_node	*root;
	int					nodes_amount;
	int					depth;
	void				*(*push_content)(t_binary_tree *self,
			t_binary_tree_node *target_node, bool push_on_left, void *content);
	void				(*push_tree)(t_binary_tree *self,
			t_binary_tree_node *target_node, bool push_on_left,
			t_binary_tree_node *new_node);
	void				*(*remove_tree)(t_binary_tree *self,
			t_binary_tree_node **node_ref, void (*free_content)(void *arg));
	void				*(*destroy)(t_binary_tree **self_ref,
			void (*free_content)(void *arg));
};

t_binary_tree	*ft_create_binary_tree(void);

#endif
