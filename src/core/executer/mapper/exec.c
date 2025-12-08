/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:41:42 by valero            #+#    #+#             */
/*   Updated: 2025/12/08 17:39:33 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapper_internal.h"

t_exec	*ft_built_exec(char **envp)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	exec->envp = envp;
	exec->ht_env = ft_init_ht_env(envp);
	exec->fds[0] = dup(STDIN_FILENO);
	exec->fds[1] = dup(STDOUT_FILENO);
	exec->destroy = false;
	return (exec);
}

void	ft_set_flag_destroy_exec(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;

	ast_node = (t_ast_node *)(node->content);
	(*(t_exec **)(ast_node->exec))->destroy = true;
}

void	ft_free_exec(void *exec)
{
	t_exec	**exec_node_ref;
	t_exec	*exec_node;

	exec_node_ref = exec;
	if (!exec_node_ref || !*exec_node_ref)
		return ;
	exec_node = *exec_node_ref;
	if (exec_node && exec_node->heredoc_files)
		exec_node->heredoc_files->destroy(
			&exec_node->heredoc_files, ft_free_heredoc_file_item);
	if (exec_node && exec_node->heredoc)
		exec_node->heredoc->destroy(&exec_node->heredoc, NULL);
	if (exec_node && exec_node->redirect)
		exec_node->redirect->destroy(
			&exec_node->redirect, ft_free_item_redirect);
	if (exec_node)
		exec_node->flag_n = 0;
	if (exec_node->destroy == true)
		ft_destroy_exec(exec_node_ref);
}

void	ft_destroy_exec(void *exec)
{
	t_exec	**exec_node_ref;
	t_exec	*exec_node;

	exec_node_ref = exec;
	if (!exec_node_ref || !*exec_node_ref)
		return ;
	exec_node = *exec_node_ref;
	if (exec_node->fds[0] != -1)
		close(exec_node->fds[0]);
	if (exec_node->fds[1] != -1)
		close(exec_node->fds[1]);
	exec_node->fds[0] = -1;
	exec_node->fds[1] = -1;
	if (exec_node->ht_env)
	{
		exec_node->ht_env->destroy(&(exec_node->ht_env), ft_free_item_ht_env);
		exec_node->ht_env = NULL;
	}
	exec_node->destroy = false;
	free(exec_node);
	*exec_node_ref = NULL;
}
