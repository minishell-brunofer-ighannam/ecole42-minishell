/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:46:26 by valero            #+#    #+#             */
/*   Updated: 2025/11/25 18:37:24 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree_internal.h"

static void	*ft_destroy_binary_tree_node(
				t_binary_tree_node **self_ref,
				void (*free_content)(void *arg));

t_binary_tree_node	*ft_create_binary_tree_node(void *content)
{
	t_binary_tree_node	*node;

	node = ft_calloc(1, sizeof(t_binary_tree_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->destroy = ft_destroy_binary_tree_node;
	return (node);
}

void	ft_get_binary_tree_node_info(
			t_binary_tree_node *node,
			t_binary_tree_node_info *info)
{
	if (!node || !info)
		return ;
	info->node_count++;
	if (node->node_depth > info->max_depth)
		info->max_depth = node->node_depth;
	if (node->left)
		ft_get_binary_tree_node_info(node->left, info);
	if (node->right)
		ft_get_binary_tree_node_info(node->right, info);
}

void	ft_update_binary_tree_node_info(t_binary_tree_node *node)
{
	if (!node)
		return ;
	node->node_depth = node->parent->node_depth + 1;
	if (node->left)
		ft_update_binary_tree_node_info(node->left);
	if (node->right)
		ft_update_binary_tree_node_info(node->right);
}

void	*ft_destroy_binary_tree_node_recursively(
			t_binary_tree_node **self_ref,
			void (*free_content)(void *arg))
{
	t_binary_tree_node	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	if (self->left)
		ft_destroy_binary_tree_node_recursively(&self->left, free_content);
	if (self->right)
		ft_destroy_binary_tree_node_recursively(&self->right, free_content);
	if (!self->left && !self->right)
		return (self->destroy(self_ref, free_content));
	return (NULL);
}

static void	*ft_destroy_binary_tree_node(
				t_binary_tree_node **self_ref,
				void (*free_content)(void *arg))
{
	t_binary_tree_node	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	free_content(self->content);
	self->left = NULL;
	self->right = NULL;
	self->parent = NULL;
	free(self);
	*self_ref = NULL;
	return (NULL);
}
