/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:42:13 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/04 12:37:43 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_exit(t_binary_tree_node *node, t_ast	*ast)
{
	if (node)
		//ft_free_argv(node);
	if (!node->parent)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	//ft_destroy_exec(((t_ast_node *)(node->content))->exec);
	if (ast)
		ast->destroy(&ast, free_ast_node);	
	exit(0);
}
