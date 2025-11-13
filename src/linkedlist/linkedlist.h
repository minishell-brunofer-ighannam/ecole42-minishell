/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:32:51 by valero            #+#    #+#             */
/*   Updated: 2025/11/13 02:09:40 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKEDLIST_H
# define LINKEDLIST_H

# include "libft.h"

/**
 * # t_linkedlist_node
 *
 * ---
 *
 * Represents a single element in a doubly-linked list.
 * Stores user content and links to neighboring nodes.
 * Includes a method to safely destroy the node.
 *
 * ## Fields
 * - `content`: Pointer to user data stored in this node.
 * - `next`: Pointer to the next node or `NULL` if last.
 * - `prev`: Pointer to previous node or `NULL` if first.
 * - `destroy`: Function to free the node and its content
 *   using a provided callback.
 *
 * ## Notes
 * - Node must be removed from any list before destruction.
 * - Ownership of `content` is transferred to the node.
 * - The `destroy` method sets the caller pointer to `NULL`.
 */
typedef struct s_linkedlist_node	t_linkedlist_node;
struct								s_linkedlist_node
{
	void							*content;
	t_linkedlist_node				*next;
	t_linkedlist_node				*prev;
	void							*(*destroy)(t_linkedlist_node **self,
									void (*free_content)(void *arg));
};

/**
 * # t_linkedlist
 *
 * ---
 *
 * Represents a complete doubly-linked list container.
 * Tracks the number of nodes and pointers to first
 * and last nodes. Provides methods to add nodes and
 * destroy the list safely.
 *
 * ## Fields
 * - `size`: Number of nodes currently in the list.
 * - `first`: Pointer to the first node, or `NULL` if empty.
 * - `last`: Pointer to the last node, or `NULL` if empty.
 * - `push`: Function to append a new node to the list.
 * - `destroy`: Function to free all nodes and the list
 *   itself, using a provided content cleanup function.
 *
 * ## Notes
 * - List owns its nodes but not their contents directly.
 * - Nodes must be destroyed through the list's destroy
 *   method to avoid leaks.
 * - After destruction, the list pointer is set to `NULL`.
 */
typedef struct s_linkedlist			t_linkedlist;
struct								s_linkedlist
{
	int								size;
	t_linkedlist_node				*first;
	t_linkedlist_node				*last;
	void							**(*to_array)(
				t_linkedlist *self, void *(*free_content)(void *arg));
	void							*(*push)(t_linkedlist *self, void *content);
	t_linkedlist_node				*(*detach)(t_linkedlist *self,
				t_linkedlist_node *node);
	void							*(*remove)(t_linkedlist *self,
				t_linkedlist_node *node,
				void (*free_content)(void *arg));
	void							*(*destroy)(t_linkedlist **self,
				void (*free_content)(void *arg));
};

t_linkedlist_node					*ft_new_linkedlist_node(void *content);
t_linkedlist						*ft_new_linkedlist(void);

#endif
