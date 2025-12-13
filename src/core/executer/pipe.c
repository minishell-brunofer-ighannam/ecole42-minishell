/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:57:56 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/13 15:28:28 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static int	ft_wait(pid_t pid_left, pid_t pid_right, int fd[2]);
static void	ft_child_left(t_binary_tree_node *node, t_ast *ast, int fd[2]);
static void	ft_child_rigth(t_binary_tree_node *node, t_ast *ast, int fd[2]);

int	ft_execute_pipe(t_binary_tree_node *node, t_ast *ast)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		fd[2];
	int		status;

	pipe(fd);
	if (ft_get_flag_n(node) == 0)
	{
		ft_init_sig_ignore();
		ft_set_flag_n(node, 1);
	}
	else
		signal(SIGINT, SIG_IGN);
	pid_left = fork();
	if (pid_left == 0)
		ft_child_left(node, ast, fd);
	pid_right = fork();
	if (pid_right == 0)
		ft_child_rigth(node, ast, fd);
	status = ft_wait(pid_left, pid_right, fd);
	ft_init_sig_parent();
	return (status);
}

static void	ft_child_left(t_binary_tree_node *node, t_ast *ast, int fd[2])
{
	int	status;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	ft_set_fd_out_pipe(node, fd[1]);
	close(fd[1]);
	status = ft_execute_node(node->left, ast);
	ft_set_flag_destroy_exec(node);
	ast->destroy(&ast, free_ast_node);
	exit(status);
}

static void	ft_child_rigth(t_binary_tree_node *node, t_ast *ast, int fd[2])
{
	int	status;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(ft_get_fd_out_pipe(node));
	status = ft_execute_node(node->right, ast);
	ft_set_flag_destroy_exec(node);
	ast->destroy(&ast, free_ast_node);
	exit(status);
}

static int	ft_wait(pid_t pid_left, pid_t pid_right, int fd[2])
{
	int	status_left;
	int	status_right;
	int	sig;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	if (WIFSIGNALED(status_right))
	{
		sig = WTERMSIG(status_right);
		return (128 + sig);
	}
	if (WIFSIGNALED(status_left))
	{
		sig = WTERMSIG(status_left);
		return (0);
	}
	if (WIFEXITED(status_right) != 0 && WEXITSTATUS(status_right) != 0)
		return (WEXITSTATUS(status_right));
	return (0);
}
