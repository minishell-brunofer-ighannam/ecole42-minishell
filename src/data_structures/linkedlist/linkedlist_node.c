/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:42:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/13 01:52:14 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linkedlist.h"

static	void	*ft_destroy_node(
					t_linkedlist_node **self, void (*free_content)(void *arg));

/**
 * # ft_new_linkedlist_node
 *
 * ---
 *
 * Allocates and initializes a new linked list node.
 * Stores user content and sets the destroy function.
 *
 * ## Logic
 * - Allocates memory for one node using `ft_calloc`.
 * - Stores the provided `content` pointer.
 * - Assigns `ft_destroy_node` as the destroy method.
 *
 * ## Parameters
 * - `content`: Pointer to the data to store in the node.
 *
 * ## Returns
 * - Pointer to the newly created node.
 * - `NULL` if memory allocation fails.
 *
 * ## Notes
 * - Ownership of `content` is passed to the node.
 * - Node must be freed using its `destroy` method.
 */
t_linkedlist_node	*ft_new_linkedlist_node(void *content)
{
	t_linkedlist_node	*node;

	node = ft_calloc(1, sizeof(t_linkedlist_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->destroy = ft_destroy_node;
	return (node);
}

/**
 * # ft_destroy_node
 *
 * ---
 *
 * Frees a linked list node and its content using a
 * provided cleanup function. Resets the node pointer
 * to `NULL` to prevent dangling references.
 *
 * ## Logic
 * - Validates input pointers.
 * - Frees `content` using `free_content` callback.
 * - Clears `next` and `prev` pointers.
 * - Frees the node structure.
 * - Sets `*self` to `NULL`.
 *
 * ## Parameters
 * - `self`: Double pointer to the node to destroy.
 * - `free_content`: Function to free the node's content.
 *
 * ## Returns
 * - Always `NULL` (for method chaining consistency).
 *
 * ## Notes
 * - Safe to call with `NULL` pointer (does nothing).
 * - Node must be removed from any list before destroying
 *   to prevent broken links.
 */
static	void	*ft_destroy_node(
					t_linkedlist_node **self, void (*free_content)(void *arg))
{
	t_linkedlist_node	*node;

	if (!self || !free_content)
		return (NULL);
	node = *self;
	free_content(node->content);
	node->next = NULL;
	node->prev = NULL;
	free(node);
	*self = NULL;
	return (NULL);
}
