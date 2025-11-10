/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:03:22 by valero            #+#    #+#             */
/*   Updated: 2025/11/10 19:13:05 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_array_structure.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:53:38 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 13:32:21 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linkedlist_array.h"

static t_linkedlist_node	*ft_linkedlist_array_push_token(
								t_linkedlist_array	*self,
								int idx, void *content);
static void	*ft_linkedlist_array_destroy(
				t_linkedlist_array **self_ref,
				void (*free_content)(void *arg));

/**
 * # ft_new_linkedlist_array
 *
 * ---
 *
 * Allocates and initializes a `t_linkedlist_array`
 * structure containing `size` independent linked lists.
 *
 * Each list is created using `ft_new_linkedlist()`,
 * preparing a clean array of lists for further use.
 *
 * ## Logic
 * - Allocates the main array structure.
 * - Sets function pointers (`push`, `destroy`).
 * - Allocates `list` array with `size + 1` entries.
 * - Initializes each list individually.
 * - On failure, destroys created lists and frees all.
 *
 * ## Parameters
 * - `size`: Number of linked lists to allocate.
 *
 * ## Return
 * - Pointer to a fully initialized `t_linkedlist_array`.
 * - `NULL` on allocation failure.
 *
 * ## Notes
 * - Each list can be accessed at index `[0..size-1]`.
 * - Internal memory cleanup ensures no leaks.
 */
t_linkedlist_array	*ft_new_linkedlist_array(int size)
{
	t_linkedlist_array	*linkedlist_array;

	linkedlist_array = ft_calloc(1, sizeof(t_linkedlist_array));
	if (!linkedlist_array)
		return (NULL);
	linkedlist_array->size = size;
	linkedlist_array->push = ft_linkedlist_array_push_token;
	linkedlist_array->destroy = ft_linkedlist_array_destroy;
	linkedlist_array->list = ft_calloc(size + 1, sizeof(t_linkedlist));
	while (--size >= 0)
	{
		linkedlist_array->list[size] = ft_new_linkedlist();
		if (!linkedlist_array->list[size])
		{
			while (++size < linkedlist_array->size)
				linkedlist_array->list[size]->destroy(
					&linkedlist_array->list[size], free);
			free(linkedlist_array);
			return (NULL);
		}
	}
	return (linkedlist_array);
}

/**
 * # ft_linkedlist_array_push_token
 *
 * ---
 *
 * Appends a new node containing `content` to the
 * linked list stored at index `idx` within the array.
 *
 * Updates the global node counter and returns a
 * pointer to the newly inserted node.
 *
 * ## Logic
 * - Checks for valid `self` and index range.
 * - Retrieves the list at given index.
 * - Calls `list->push()` to append content.
 * - Increments `nodes_amount` counter.
 * - Returns pointer to the last node.
 *
 * ## Parameters
 * - `self`: The `t_linkedlist_array` instance.
 * - `idx`: Target list index.
 * - `content`: Pointer to data to be added.
 *
 * ## Return
 * - Pointer to the newly added node.
 * - `NULL` if invalid input or index out of range.
 *
 * ## Notes
 * - The pushed node becomes the last element
 *   of the selected linked list.
 * - Content ownership remains with the caller.
 */
static t_linkedlist_node	*ft_linkedlist_array_push_token(
				t_linkedlist_array	*self, int idx, void *content)
{
	t_linkedlist	*list;

	if (!self || idx > self->size - 1)
		return (NULL);
	list = self->list[idx];
	list->push(list, content);
	self->nodes_amount++;
	return (list->last);
}

/**
 * # ft_linkedlist_array_destroy
 *
 * ---
 *
 * Releases all memory used by a `t_linkedlist_array`,
 * including its lists and their contents.
 *
 * Each internal list is destroyed using the provided
 * `free_content` callback for stored nodes.
 *
 * ## Logic
 * - Iterates over all lists in reverse order.
 * - Calls each list’s `destroy()` function.
 * - Frees `list` array and main structure.
 * - Sets reference pointer to `NULL`.
 *
 * ## Parameters
 * - `self_ref`: Pointer to the structure reference.
 * - `free_content`: Function to free node content.
 *
 * ## Return
 * - Always returns `NULL` for chaining cleanup.
 *
 * ## Notes
 * - Safe to call with partially initialized arrays.
 * - Prevents memory leaks by cleaning nested lists.
 */
static void	*ft_linkedlist_array_destroy(
		t_linkedlist_array **self_ref, void (*free_content)(void *arg))
{
	t_linkedlist_array	*self;
	t_linkedlist		*list;

	self = *self_ref;
	while (--self->size >= 0)
	{
		list = self->list[self->size];
		list->destroy(&list, free_content);
	}
	free(self->list);
	free(self);
	*self_ref = NULL;
	return (NULL);
}
