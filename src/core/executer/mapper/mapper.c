/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:54:45 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/04 20:36:26 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapper.h"

t_exec	*ft_built_exec(char **envp)
{
	t_exec *exec;

	exec = ft_calloc(1, sizeof(t_exec));
	exec->envp = envp;
	exec->ht_env = ft_init_ht_env(envp);
	exec->fds[0] = dup(STDIN_FILENO);
	exec->fds[1] = dup(STDOUT_FILENO);
	exec->destroy = ft_calloc(1, sizeof(bool));
	return (exec);
}

void ft_free_exec(void *exec)
{
	t_exec *exec_node;

	if (!exec)
		return ;
	exec_node = (t_exec *)exec;
	if (exec_node && exec_node->heredoc)
	{
		exec_node->heredoc->destroy(&exec_node->heredoc, NULL);
		exec_node->heredoc = NULL;
	}
	if (exec_node && exec_node->argv)
	{
		free(exec_node->argv);
		exec_node->argv = NULL;
	}
	if (exec_node && exec_node->redirect)
	{
		exec_node->redirect->destroy(&exec_node->redirect, ft_free_item_redirect);
		exec_node->redirect = NULL;
	}
}

void ft_set_flag_destroy_exec(t_binary_tree_node *node)
{
	t_ast_node *ast_node;

	ast_node = (t_ast_node *)(node->content);
	*(((t_exec *)(ast_node->exec))->destroy) = true;
}

int ft_get_fd_in(t_binary_tree_node *node)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	return(exec->fds[0]);
}

int ft_get_fd_out(t_binary_tree_node *node)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	return(exec->fds[1]);
}

void ft_close_fds(t_binary_tree_node *node)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	close(exec->fds[0]);
	close(exec->fds[1]);
}

t_linkedlist_array *ft_get_ht_env(t_binary_tree_node *node)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	return(exec->ht_env);
}

t_token	**ft_get_tokens(t_binary_tree_node *node)
{
	t_ast_node *ast_node;

	ast_node = (t_ast_node *)(node->content);
	return(ast_node->tokens);
}

t_ast_node_type	ft_get_type(t_binary_tree_node *node)
{
	t_ast_node *ast_node;

	ast_node = (t_ast_node *)(node->content);
	return(ast_node->type);
}

t_linkedlist **ft_get_list_redirects(t_binary_tree_node *node)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	return(&exec->redirect);
}

char **ft_get_argv(t_binary_tree_node *node)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	return(exec->argv);
}

char **ft_get_envp(t_binary_tree_node *node)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	return(exec->envp);
}

void ft_init_argv(t_binary_tree_node *node, int size)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	exec->argv = ft_calloc(size, sizeof(char *));
}

void ft_set_argv(t_binary_tree_node *node, int index, char *str)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	exec->argv[index] = str;
}

void ft_free_argv(t_binary_tree_node *node)
{
	t_ast_node *ast_node;
	t_exec *exec;

	if (!node)
		return ;
	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	free(exec->argv);
}

void ft_push_redirect(t_binary_tree_node *node, t_redirect *content)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	exec->redirect->push(exec->redirect, content);
}

void ft_set_redirect(t_binary_tree_node *node, t_linkedlist *list)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	exec->redirect = list;
}

void	ft_init_redirect(t_binary_tree_node *node)
{
	t_ast_node *ast_node;
	t_exec *exec;

	ast_node = (t_ast_node *)(node->content);
	exec = (t_exec *)(ast_node->exec);
	exec->redirect = ft_new_linkedlist();
}
