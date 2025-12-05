/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:22:09 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/04 19:10:57 by ighannam         ###   ########.fr       */
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
		//ft_destroy_exec(((t_ast_node *)(((t_binary_tree_node *)(ast->tree->root))->content))->exec);
		ft_set_flag_destroy_exec(node);
		ast->destroy(&ast, free_ast_node);
		exit(status);
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		//ft_free_argv(node);
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status) != 0 && WEXITSTATUS(status) != 0)
	{
		//ft_free_argv(node);
		return (WEXITSTATUS(status));
	}
	return (status);
}
