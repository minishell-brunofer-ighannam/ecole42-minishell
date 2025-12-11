/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:04:15 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/10 22:26:26 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void	ft_verify_path_cmd(char *path, t_binary_tree_node *node, t_ast *ast,
				int status);
static int	ft_wait_cmd(char *path, pid_t pid, t_binary_tree_node *node);
static int	ft_execute_not_built_in(t_binary_tree_node *node, t_ast *ast);
static void	ft_child(char *path, t_binary_tree_node *node, t_ast *ast,
				int status);

int	ft_execute_cmd(t_binary_tree_node *node, t_ast *ast)
{
	int	status;

	status = 0;
	// ft_built_args(node);
	ft_build_args_alternative(node);
	if (ft_execute_redirect(node) == 1)
	{
		ft_free_argv(node);
		return (1);
	}
	if (ft_get_argv(node)[0] == NULL)
	{
		ft_free_argv(node);
		return (status);
	}
	if (ft_is_builtin(ft_get_tokens(node)[0]->last_build->token_expanded) == 1)
	{
		status = ft_execute_builtin(node, ast);
		ft_free_argv(node);
		return (status);
	}
	status = ft_execute_not_built_in(node, ast);
	ft_clean_redirect(node);
	dup2(ft_get_fd_out(ast->tree->root), STDOUT_FILENO);
	dup2(ft_get_fd_in(ast->tree->root), STDIN_FILENO);
	return (status);
}

static int	ft_execute_not_built_in(t_binary_tree_node *node, t_ast *ast)
{
	char	*path;
	int		status;
	pid_t	pid;

	status = 0;
	path = ft_find_path(ft_get_ht_env(node), ft_get_argv(node)[0]);
	if (!path)
		status = 127;
	else
	{
		if (ft_get_flag_n(node) == 0)
		{
			ft_init_sig_ignore();
			ft_set_flag_n(node, 1);
		}
		else
			signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			ft_child(path, node, ast, status);
		status = ft_wait_cmd(path, pid, node);
	}
	ft_free_argv(node);
	return (status);
}

static void	ft_child(char *path, t_binary_tree_node *node, t_ast *ast,
		int status)
{
	ft_verify_path_cmd(path, node, ast, status);
	ft_init_sig_child();
	status = execve(path, ft_get_argv(node), ft_get_envp(node));
	ft_destroy_tree_cmd(path, node, ast);
	exit(126);
}

static void	ft_verify_path_cmd(char *path, t_binary_tree_node *node, t_ast *ast,
		int status)
{
	struct stat	s;

	if (stat(path, &s) == -1)
	{
		if (errno == EACCES || errno == ENOENT)
			ft_print_error_cmd(errno, path);
		if (errno == EACCES)
			status = 126;
		if (errno == ENOENT)
			status = 127;
		ft_destroy_tree_cmd(path, node, ast);
		exit(status);
	}
	if (S_ISDIR(s.st_mode))
		ft_print_error_cmd(0, path);
	if (!(s.st_mode & S_IXUSR))
		ft_print_error_cmd(1, path);
	if (S_ISDIR(s.st_mode) || !(s.st_mode & S_IXUSR))
	{
		ft_destroy_tree_cmd(path, node, ast);
		exit(126);
	}
}

static int	ft_wait_cmd(char *path, pid_t pid, t_binary_tree_node *node)
{
	int	status;
	int	sig;

	status = 0;
	waitpid(pid, &status, 0);
	ft_init_sig_parent();
	free(path);
	ft_free_argv(node);
	if (WIFEXITED(status) != 0 && WEXITSTATUS(status) != 0)
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		return (128 + sig);
	}
	return (status);
}
