/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:16:08 by valero            #+#    #+#             */
/*   Updated: 2025/11/25 21:35:21 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree_internal.h"

static void	*ft_push_binary_tree(
				t_binary_tree *self,
				t_binary_tree_node *target_node,
				bool push_on_left,
				t_binary_tree_node *new_node);
static void	*ft_remove_binary_tree(
				t_binary_tree *self,
				t_binary_tree_node **node_ref,
				void (*free_content)(void *arg));
static void	*ft_destroy_binary_tree(
				t_binary_tree **self_ref,
				void (*free_content)(void *arg));

t_binary_tree	*ft_create_binary_tree(void)
{
	t_binary_tree	*tree;

	tree = ft_calloc(1, sizeof(t_binary_tree));
	if (!tree)
		return (NULL);
	tree->push_tree = ft_push_binary_tree;
	tree->push_content = ft_push_binary_tree_content;
	tree->remove_tree = ft_remove_binary_tree;
	tree->destroy = ft_destroy_binary_tree;
	return (tree);
}

static void	*ft_push_binary_tree_content(
				t_binary_tree *self,
				t_binary_tree_node *target_node,
				bool push_on_left,
				void *content)
{
	t_binary_tree_node	*new_node;

	if (!self || (!self->root && target_node) || (target_node
			&& ((push_on_left && target_node->left)
				|| (!push_on_left && target_node->right))))
		return (NULL);
	new_node = ft_create_binary_tree_node(content);
	if (!new_node)
		return (NULL);
	self->nodes_amount++;
	if (!self->root)
	{
		self->root = new_node;
		return (NULL);
	}
	if (push_on_left)
		target_node->left = new_node;
	else
		target_node->right = new_node;
	new_node->node_depth = target_node->node_depth + 1;
	if (new_node->node_depth > self->depth)
		self->depth = new_node->node_depth;
	return (NULL);
}

static void	*ft_push_binary_tree(
				t_binary_tree *self,
				t_binary_tree_node *node,
				bool onleft,
				t_binary_tree_node *new_node)
{
	t_binary_tree_node_info	info;
	int						new_depth;

	if (!self || !new_node || (!self->root && node) || (node
			&& ((onleft && node->left) || (!onleft && node->right))))
		return (NULL);
	if (!self->root)
	{
		self->root = new_node;
		new_node->node_depth = 0;
		node = new_node;
	}
	ft_bzero(&info, sizeof(t_binary_tree_node_info));
	ft_get_binary_tree_node_info(new_node, &info);
	new_depth = node->node_depth + info.max_depth + (self->root != new_node);
	if (new_depth > self->depth)
		self->depth = new_depth;
	new_node->node_depth = node->node_depth + (self->root != new_node);
	ft_update_binary_tree_node_info(new_node->left);
	ft_update_binary_tree_node_info(new_node->right);
	self->nodes_amount += info.node_count;
	if (self->root != new_node && onleft)
		node->left = new_node;
	else if (self->root != new_node && !onleft)
		node->right = new_node;
}

static void	*ft_remove_binary_tree(
				t_binary_tree *self,
				t_binary_tree_node **node_ref,
				void (*free_content)(void *arg))
{
	t_binary_tree_node_info	info;

	if (!self || !node_ref || !*node_ref)
		return (NULL);
	ft_destroy_binary_tree_node_recursively(node_ref, free_content);
	ft_bzero(&info, sizeof(t_binary_tree_node_info));
	ft_get_binary_tree_node_info(self->root, &info);
	self->nodes_amount = info.node_count;
	self->depth = info.max_depth;
	return (NULL);
}

static void	*ft_destroy_binary_tree(
				t_binary_tree **self_ref,
				void (*free_content)(void *arg))
{
	t_binary_tree	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	ft_remove_binary_tree(self, &self->root, free_content);
	free(self);
	*self_ref = NULL;
	return (NULL);
}
