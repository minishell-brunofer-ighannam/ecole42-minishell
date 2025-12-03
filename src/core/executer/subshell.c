/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:22:09 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/03 11:27:37 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_subshell(t_binary_tree_node *node, t_ast *ast)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		status = ft_execute_node(node->left, ast);
		ft_destroy_exec(((t_ast_node *)(((t_binary_tree_node *)(ast->tree->root))->content))->exec);
		ast->destroy(&ast, free_ast_node);
		exit(status);
	}
	waitpid(pid, &status, 0);
	return (status);
}
