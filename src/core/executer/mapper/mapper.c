/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:54:45 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/03 10:59:01 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapper.h"

t_exec	*ft_built_exec(char **envp)
{
	t_exec *exec;

	exec = ft_calloc(1, sizeof(t_exec));
	exec->envp = envp;
	exec->ht_env = ft_init_ht_env(envp);
	return (exec);
}

void ft_destroy_exec(t_exec *exec)
{
	if (!exec)
		return ;
	exec->ht_env->destroy(&(exec->ht_env), ft_free_item_ht_env);
	free(exec);
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
