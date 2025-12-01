/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:12:06 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/01 08:22:50 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_execute_or(t_binary_tree_node *node)
{
	int status;

	status = ft_execute_node(node->left);
	if (status != 0)
		status = ft_execute_node(node->right);
	return (status);
}
