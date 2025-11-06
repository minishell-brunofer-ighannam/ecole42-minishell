/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:32:51 by valero            #+#    #+#             */
/*   Updated: 2025/11/06 17:25:34 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKEDLIST_H
# define LINKEDLIST_H

# include "libft.h"

typedef struct s_linkedlist_node	t_linkedlist_node;
struct s_linkedlist_node
{
	t_linkedlist_node	**self_ref;
	void				*content;
	t_linkedlist_node	*next;
	t_linkedlist_node	*prev;
	void				*(*destroy)(
			t_linkedlist_node *self, void (*free_content)(void *arg));
};

typedef struct s_linkedlist			t_linkedlist;
struct s_linkedlist
{
	t_linkedlist		**self_ref;
	int					size;
	t_linkedlist_node	*first;
	t_linkedlist_node	*last;
	void				*(*push)(void *content);
	void				*(*destroy)(
			t_linkedlist *self, void (*free_content)(void *arg));
};

t_linkedlist_node	*ft_new_node(void *content);
t_linkedlist		*ft_new_linkedlist(void);

#endif
