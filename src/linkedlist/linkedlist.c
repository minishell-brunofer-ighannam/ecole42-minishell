/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:52:21 by valero            #+#    #+#             */
/*   Updated: 2025/11/10 23:18:47 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linkedlist.h"

static void					*ft_linkedlist_destroy(t_linkedlist **self,
								void (*free_content)(void *arg));
static void					*ft_push_new_node(t_linkedlist *self,
								void *content);
static t_linkedlist_node	*ft_detach_node(t_linkedlist *self,
								t_linkedlist_node *node);
static void					*ft_remove_node(t_linkedlist *self,
								t_linkedlist_node *node,
								void (*free_content)(void *arg));
static void ft_iteri_linkedlist(t_linkedlist *self, void (*ft_iteri)(void *arg));

/**
 * # ft_new_linkedlist
 *
 * ---
 *
 * Allocates and initializes an empty doubly-linked list.
 * Sets method pointers for node insertion and list
 * destruction.
 *
 * ## Logic
 * - Allocates memory for the list via `ft_calloc`.
 * - Assigns `push` and `destroy` method pointers.
 *
 * ## Parameters
 * - *(none)*
 *
 * ## Returns
 * - Pointer to the newly created list.
 * - `NULL` if memory allocation fails.
 *
 * ## Notes
 * - List starts empty (`size == 0`, `first == NULL`).
 * - Nodes added must be freed via the list's destroy method.
 */
t_linkedlist	*ft_new_linkedlist(void)
{
	t_linkedlist	*linkedlist;

	linkedlist = ft_calloc(1, sizeof(t_linkedlist));
	if (!linkedlist)
		return (NULL);
	linkedlist->push = ft_push_new_node;
	linkedlist->iteri = ft_iteri_linkedlist;
	linkedlist->detach = ft_detach_node;
	linkedlist->remove = ft_remove_node;
	linkedlist->destroy = ft_linkedlist_destroy;
	return (linkedlist);
}

/**
 * # ft_push_new_node
 *
 * ---
 *
 * Creates a new node and appends it to the end of the
 * linked list. Updates `first`, `last`, and `size`
 * accordingly.
 *
 * ## Logic
 * - Allocates a new node using `ft_new_node`.
 * - Increments the list `size`.
 * - If the list was empty → sets `first` and `last`.
 * - Otherwise → links node after `last` and updates tail.
 *
 * ## Parameters
 * - `self`: Pointer to the target linked list.
 * - `content`: Pointer to data to store in the new node.
 *
 * ## Returns
 * - Always `NULL` (for method chaining consistency).
 *
 * ## Notes
 * - If allocation fails, the list remains unchanged.
 * - The node assumes ownership of `content`.
 */
static void	*ft_push_new_node(t_linkedlist *self, void *content)
{
	t_linkedlist_node	*node;

	node = ft_new_node(content);
	if (!node)
		return (NULL);
	self->size++;
	if (self->size == 1)
	{
		self->first = node;
		self->last = node;
		return (NULL);
	}
	node->prev = self->last;
	self->last->next = node;
	self->last = node;
	return (NULL);
}

static void ft_iteri_linkedlist(t_linkedlist *self, void (*ft_iteri)(void *arg))
{
	t_linkedlist_node *node;

	if (!self)
		return ;
	node = self->first;
	while (node)
	{
		ft_iteri(node);
		node = node->next;
	}
}

static t_linkedlist_node	*ft_detach_node(t_linkedlist *self,
		t_linkedlist_node *node)
{
	t_linkedlist_node	*prev;
	t_linkedlist_node	*next;

	prev = node->prev;
	next = node->next;
	if (self->first == node)
		self->first = node->next;
	if (self->last == node)
		self->last = node->prev;
	if (prev)
		prev->next = node->next;
	if (next)
		next->prev = node->prev;
	node->next = NULL;
	node->prev = NULL;
	self->size--;
	return (node);
}

static void	*ft_remove_node(t_linkedlist *self, t_linkedlist_node *node,
		void (*free_content)(void *arg))
{
	t_linkedlist_node	*removed;

	removed = ft_detach_node(self, node);
	return (removed->destroy(&removed, free_content));
}

/**
 * # ft_linkedlist_destroy
 *
 * ---
 *
 * Frees an entire linked list and all its nodes. Each
 * node's content is freed using the provided function.
 * The list pointer is set to `NULL` to prevent dangling
 * references.
 *
 * ## Logic
 * - Validates the list pointer.
 * - Iterates through all nodes, calling their destroy
 *   method with `free_content` callback.
 * - Frees the list structure itself.
 * - Sets the list pointer to `NULL`.
 *
 * ## Parameters
 * - `self`: Double pointer to the linked list to destroy.
 * - `free_content`: Function to free each node's content.
 *
 * ## Returns
 * - Always `NULL` (for method chaining consistency).
 *
 * ## Notes
 * - Safe to call with an empty or `NULL` list.
 * - All nodes must be destroyed through this method
 *   to avoid memory leaks.
 */
static void	*ft_linkedlist_destroy(t_linkedlist **self,
		void (*free_content)(void *arg))
{
	t_linkedlist_node	*curr_node;
	t_linkedlist_node	*next_node;
	t_linkedlist		*list;

	if (!self || !*self)
		return (NULL);
	list = *self;
	if (list->size)
	{
		curr_node = list->first;
		next_node = curr_node->next;
		while (curr_node)
		{
			curr_node->destroy(&curr_node, free_content);
			curr_node = next_node;
			if (curr_node)
				next_node = curr_node->next;
		}
	}
	free(list);
	*self = NULL;
	return (NULL);
}
