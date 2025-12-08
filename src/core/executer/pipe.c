/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:57:56 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/08 17:06:40 by ighannam         ###   ########.fr       */
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
	// if (node->node_depth == 0 || node->node_depth == 1)
	// {
	// 	if (node->node_depth == 1)
	// 	{
	// 		if (ft_get_type(node->parent) != AST_NODE_PIPE && ft_get_type(node->parent) != AST_NODE_SUBSHELL)
	// 			ft_init_sig_ignore();
	// 		else
	// 			signal(SIGINT, SIG_IGN);
	// 	}
	// 	else
	// 		ft_init_sig_ignore();
	// }
	// else
	// 	signal(SIGINT, SIG_IGN);
	
	//if flag == 0 --> ft_init_sig_ignore() + seta flag para 1; else signal(SIGINT, SIG_IGN);
	pid_left = fork();
	if (pid_left == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		status = ft_execute_node(node->left, ast);
		ft_set_flag_destroy_exec(node);
		ast->destroy(&ast, free_ast_node);
		exit(status);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(fd[1]);
		if (ft_get_type(node->right) != AST_NODE_HERE_DOC_IN 
		&& ft_get_type(node->right) != AST_NODE_REDIRECT_IN)
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		status = ft_execute_node(node->right, ast);
		ft_set_flag_destroy_exec(node);
		ast->destroy(&ast, free_ast_node);
		exit(status);
	}
	status = ft_wait(pid_left, pid_right, fd);
	ft_init_sig_parent();
	return (status);
}

static int	ft_wait(pid_t pid_left, pid_t pid_right, int fd[2])
{
	int	status_left;
	int	status_right;
	int sig;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	if (WIFSIGNALED(status_right))
    {
        int sig = WTERMSIG(status_right);
        // if (sig == SIGINT)
        //     write(1, "\n", 1);
        return 128 + sig;
    }
	if (WIFSIGNALED(status_left))
	{
		sig = WTERMSIG(status_left);
		// if (sig == SIGINT) 
		// 	   write(1, "\n", 1);
		return (128 + sig);
	}
	if (WIFEXITED(status_right) != 0 && WEXITSTATUS(status_right) != 0)
		return (WEXITSTATUS(status_right));
	return (0);
}
