/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:57:56 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/03 14:47:52 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static int	ft_wait(pid_t pid_left, pid_t pid_right, int fd[2]);

int	ft_execute_pipe(t_binary_tree_node *node, t_ast	*ast)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		fd[2];
	int status;

	pipe(fd);
	pid_left = fork();
	if (pid_left == 0)
	{
		ft_handle_sig_child();
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		status = ft_execute_node(node->left, ast);
		ft_destroy_exec(((t_ast_node *)(((t_binary_tree_node *)(ast->tree->root))->content))->exec);
		ast->destroy(&ast, free_ast_node);
		exit(status);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		ft_handle_sig_child();
		close(fd[1]);
		if (ft_get_type(node->right) != AST_NODE_HERE_DOC_IN 
			&& ft_get_type(node->right) != AST_NODE_REDIRECT_IN)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		status = ft_execute_node(node->right, ast);
		ft_destroy_exec(((t_ast_node *)(((t_binary_tree_node *)(ast->tree->root))->content))->exec);
		ast->destroy(&ast, free_ast_node);
		exit(status);
	}
	return (ft_wait(pid_left, pid_right, fd));
}

static int	ft_wait(pid_t pid_left, pid_t pid_right, int fd[2])
{
	int	status_left;
	int	status_right;

	close(fd[0]);
	close(fd[1]);
	if (waitpid(pid_left, &status_left, 0) == -1 || waitpid(pid_right,
			&status_right, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status_right) != 0 && WEXITSTATUS(status_right) != 0)
		return (WEXITSTATUS(status_right));
	return (0);
}
