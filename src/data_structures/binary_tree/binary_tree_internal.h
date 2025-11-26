/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:23:55 by valero            #+#    #+#             */
/*   Updated: 2025/11/25 18:37:35 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_INTERNAL_H
# define BINARY_TREE_INTERNAL_H

# include "binary_tree.h"
# include "libft.h"
# include <stdbool.h>

typedef struct s_binary_tree_node_info	t_binary_tree_node_info;
struct s_binary_tree_node_info
{
	int	node_count;
	int	max_depth;
};

void				*ft_destroy_binary_tree_node_recursively(
						t_binary_tree_node **self_ref,
						void (*free_content)(void *arg));
t_binary_tree_node	*ft_create_binary_tree_node(void *content);
void				ft_update_binary_tree_node_info(t_binary_tree_node *node);
void				ft_get_binary_tree_node_info(
						t_binary_tree_node *node,
						t_binary_tree_node_info *info);

#endif
