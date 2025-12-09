/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:40:23 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/09 14:38:08 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static int	ft_ret_not_zero(int ret, t_binary_tree_node *node, t_ast *ast);

int	ft_execute_tree(t_ast *ast)
{
	int					ret;
	char				*key_value;
	char				*value;
	t_binary_tree_node	*node;

	node = ast->tree->root;
	ret = ft_execute_heredocs(node);
	ft_init_sig_parent();
	if (ret != 0)
		return (ft_ret_not_zero(ret, node, ast));
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

int	ft_execute_node(t_binary_tree_node *node, t_ast *ast)
{
	int	ret;

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

static int	ft_ret_not_zero(int ret, t_binary_tree_node *node, t_ast *ast)
{
	char	*value;
	char	*key_value;

	value = ft_itoa(ret);
	key_value = ft_strjoin("?=", value);
	ft_set(ft_get_ht_env(node), key_value);
	free(key_value);
	free(value);
	ast->destroy(&ast, free_ast_node);
	return (ret);
}
