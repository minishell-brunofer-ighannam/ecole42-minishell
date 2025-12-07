/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:32:51 by valero            #+#    #+#             */
/*   Updated: 2025/12/07 20:12:24 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKEDLIST_INTERNAL_H
# define LINKEDLIST_INTERNAL_H

# include "libft.h"

typedef struct s_linkedlist_node	t_linkedlist_node;
typedef struct s_linkedlist			t_linkedlist;

void	ft_iteri_linkedlist(t_linkedlist *self, void (*ft_iteri)(void *arg));
void	**ft_linkedlist_to_array(
			t_linkedlist *self,
			void *(*dup_content)(void *content),
			void (*free_content)(void *content));

#endif
