/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:12:06 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/08 20:28:59 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_execute_or(t_binary_tree_node *node, t_ast *ast)
{
	int	status;

	status = ft_execute_node(node->left, ast);
	if (status != 0 && ft_get_sig() != SIGINT)
		status = ft_execute_node(node->right, ast);
	return (status);
}
