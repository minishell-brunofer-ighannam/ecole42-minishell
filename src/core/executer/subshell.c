/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:22:09 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/09 12:49:19 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wait_subshell(pid_t pid);
static void	ft_child_subshell(t_binary_tree_node *node, t_ast *ast);

int	ft_execute_subshell(t_binary_tree_node *node, t_ast *ast)
{
	int			status;
	pid_t		pid;
	t_exec		*exec;
	t_ast_node	*ast_node;

	ast_node = (t_ast_node *)(node->content);
	exec = (*(t_exec **)(ast_node->exec));
	if (ft_get_flag_n(node) == 0)
	{
		ft_init_sig_ignore();
		ft_set_flag_n(node, 1);
	}
	else
		signal(SIGINT, SIG_IGN);
	if (ft_execute_redirect(node) == 1)
		return (1);
	if (exec && exec->redirect)
		exec->redirect->destroy(&exec->redirect, ft_free_item_redirect);
	pid = fork();
	if (pid == 0)
		ft_child_subshell(node, ast);
	status = ft_wait_subshell(pid);
	ft_init_sig_parent();
	return (status);
}

static void	ft_child_subshell(t_binary_tree_node *node, t_ast *ast)
{
	int	status;

	status = ft_execute_node(node->left, ast);
	ft_set_flag_destroy_exec(node);
	ast->destroy(&ast, free_ast_node);
	exit(status);
}

static int	ft_wait_subshell(pid_t pid)
{
	int	status;
	int	sig;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) != 0 && WEXITSTATUS(status) != 0)
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		return (128 + sig);
	}
	return (status);
}
