/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:32:51 by valero            #+#    #+#             */
/*   Updated: 2025/11/13 02:08:03 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKEDLIST_INTERNAL_H
# define LINKEDLIST_INTERNAL_H

# include "libft.h"

typedef struct s_linkedlist_node	t_linkedlist_node;
typedef struct s_linkedlist			t_linkedlist;

void	**ft_linkedlist_to_array(
			t_linkedlist *self, void *(*free_content)(void *arg));

#endif
