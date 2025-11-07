/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:42:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/06 16:54:40 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linkedlist.h"

static	void	*ft_destroy_node(
					t_linkedlist_node	*node, void (*free_content)(void *arg));

t_linkedlist_node	*ft_new_node(void *content)
{
	t_linkedlist_node	*node;

	node = ft_calloc(1, sizeof(t_linkedlist_node));
	if (!node)
		return (NULL);
	node->self_ref = &node;
	node->content = content;
	node->destroy = ft_destroy_node;
}

static	void	*ft_destroy_node(
					t_linkedlist_node	*node, void (*free_content)(void *arg))
{
	t_linkedlist_node	**self_ref;

	if (!node || !free_content)
		return (NULL);
	self_ref = node->self_ref;
	free_content(node->content);
	node->next = NULL;
	node->prev = NULL;
	free(node);
	*self_ref = NULL;
}
