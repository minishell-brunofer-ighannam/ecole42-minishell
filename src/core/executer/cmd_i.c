/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:04:15 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/08 17:43:10 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void ft_destroy_tree_cmd(char *path, t_binary_tree_node *node, t_ast *ast);
static void ft_verify_path_cmd(char *path, t_binary_tree_node *node, t_ast *ast, int status);
static int ft_wait_cmd(char *path, pid_t pid, t_binary_tree_node *node);
static int ft_execute_not_built_in(t_binary_tree_node *node, t_ast *ast);

int ft_execute_cmd(t_binary_tree_node *node, t_ast *ast)
{
	int status;

	status = 0;
	ft_built_args(node);
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
	return (status);
}

static int ft_execute_not_built_in(t_binary_tree_node *node, t_ast *ast)
{
	char *path;
	int status;
	pid_t pid;
	
	status = 0;
	path = ft_find_path(ft_get_ht_env(node), ft_get_argv(node)[0]);
	if (!path)
	{
		ft_free_argv(node);
		status = 127;
	}
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
		{
			ft_verify_path_cmd(path, node, ast, status);
			ft_init_sig_child();
			status = execve(path, ft_get_argv(node), ft_get_envp(node));
			ft_destroy_tree_cmd(path, node, ast);
			exit (126);		
		}
		status = ft_wait_cmd(path, pid, node);
		ft_init_sig_parent();
	}
	return (status);
}

static void ft_destroy_tree_cmd(char *path, t_binary_tree_node *node, t_ast *ast)
{
	free(path);
	ft_free_argv(node);
	ft_set_flag_destroy_exec(node);
	ast->destroy(&ast, free_ast_node);
}

static void ft_verify_path_cmd(char *path, t_binary_tree_node *node, t_ast *ast, int status)
{
	struct stat s;

	if (stat(path, &s) == -1)
	{
		if (errno == EACCES || errno == ENOENT)
			ft_print_error_cmd(errno, path);
		if (errno == EACCES)
			status = 126;
		if (errno == ENOENT)
			status = 127;
		ft_destroy_tree_cmd(path, node, ast);
		exit (status);
	}
	if (S_ISDIR(s.st_mode))
		ft_print_error_cmd(0, path);
	if (!(s.st_mode & S_IXUSR))
		ft_print_error_cmd(1, path);
	if (S_ISDIR(s.st_mode) || !(s.st_mode & S_IXUSR))
	{
		ft_destroy_tree_cmd(path, node, ast);
		exit (126);
	}
}

static int ft_wait_cmd(char *path, pid_t pid, t_binary_tree_node *node)
{
	int status;
	int sig;

	status = 0;
	waitpid(pid, &status, 0);
	free(path);
	ft_free_argv(node);
	if (WIFEXITED(status) != 0 && WEXITSTATUS(status) != 0)
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		// if (sig == SIGINT) 
       	// 	write(1, "\n", 1);
    	return (128 + sig);
	}
	return (status);
}
