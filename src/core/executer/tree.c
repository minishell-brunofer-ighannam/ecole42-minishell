/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:40:23 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/03 16:01:00 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_execute_tree(t_ast *ast)
{
	int ret;
	char *key_value;
	char *value;
	t_binary_tree_node *node;

	node = ast->tree->root;
	ret = ft_execute_heredocs(node); //primeiro percorrer toda a árvore e tratar todos os heredocs. Se algum der errado (ctrl C), nem executa mais nada.
	if (ret != 0)
	{
		value = ft_itoa(ret);
		key_value = ft_strjoin("?=", value);
		ft_set(ft_get_ht_env(node), key_value);
		free(key_value);
		free(value);
		ast->destroy(&ast, free_ast_node);
		return (1);
	}
	ret = ft_execute_node(node, ast);
	value = ft_itoa(ret);
	key_value = ft_strjoin("?=", value);
	ft_set(ft_get_ht_env(node), key_value);
	free(key_value);
	free(value);
	dup2(ft_get_fd_out(ast->tree->root), STDOUT_FILENO);
	dup2(ft_get_fd_in(ast->tree->root), STDIN_FILENO);
	ast->destroy(&ast, free_ast_node);
	return (ret);
}

int ft_execute_node(t_binary_tree_node *node, t_ast	*ast)
{
	int ret;

	ret = 0;
	if (ft_is_redirect(node) == 1)
	{
		ft_init_redirect(node);
		ret = ft_visit_redirect(node, ast);
	}
	if (ft_get_type(node) == AST_NODE_CMD)
		ret = ft_execute_cmd(node, ast);
	if (ft_get_type(node) == AST_NODE_PIPE)
		ret = ft_execute_pipe(node, ast);
	if (ft_get_type(node) == AST_NODE_AND)
		ret = ft_execute_and(node, ast);
	if (ft_get_type(node) == AST_NODE_OR)
		ret = ft_execute_or(node, ast);
	if (ft_get_type(node) == AST_NODE_SUBSHELL)
		ret = ft_execute_subshell(node, ast);
	return (ret);
}

void	free_ast_node(void *arg)
{
	t_ast_node	*node;

	if (!arg)
		return ;
	node = (t_ast_node *)arg;
	node->destroy(&node, NULL);
}


