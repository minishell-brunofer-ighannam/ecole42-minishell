/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_array.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:03:40 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 22:40:40 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKEDLIST_ARRAY_H
# define LINKEDLIST_ARRAY_H

# include "../linkedlist/linkedlist.h"

/**
 * # t_linkedlist_array
 *
 * ---
 *
 * Represents a dynamic array of linked lists,
 * allowing grouped list operations and centralized
 * memory management.
 *
 * Each index in `list` points to an independent
 * `t_linkedlist`, supporting modular token storage
 * or categorized data grouping.
 *
 * ## Fields
 * - `size`: Number of lists contained.
 * - `nodes_amount`: Total nodes across all lists.
 * - `list`: Array of `t_linkedlist` pointers.
 * - `push`: Adds a new node in a given list index.
 * - `destroy`: Frees all lists and resets pointer.
 *
 * ## Notes
 * - Ownership of stored content is delegated to
 *   the caller’s provided free function.
 * - Ensures consistency when multiple linked lists
 *   are needed under a single structure.
 */
typedef struct s_linkedlist_array	t_linkedlist_array;
struct s_linkedlist_array
{
	int					size;
	int					nodes_amount;
	t_linkedlist		**list;
	t_linkedlist_node	*(*push)(
			t_linkedlist_array *self, int idx, void *content);
	void				*(*destroy)(
			t_linkedlist_array **self, void (*free_content)(void *arg));
};

t_linkedlist_array	*ft_new_linkedlist_array(int size);

#endif
