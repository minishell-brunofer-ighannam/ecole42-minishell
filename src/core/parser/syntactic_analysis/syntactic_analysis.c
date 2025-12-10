/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:25:32 by valero            #+#    #+#             */
/*   Updated: 2025/12/10 12:18:28 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntactic_analysis_internal.h"

static void	ft_analyse_tree_nodes(t_binary_tree_node *node, t_lexer *lexer);

void	ft_syntactic_analysis(t_ast *ast)
{
	if (!ast || !ast->lexer || !ast->tree || !ast->tree->root)
		return ;
	ft_analyse_tree_nodes(ast->tree->root, ast->lexer);
}

static void	ft_analyse_tree_nodes(t_binary_tree_node *node, t_lexer *lexer)
{
	t_ast_node	*content;

	if (!node || !node->content)
		return ;
	content = node->content;
	if (ft_is_logic_node(content))
		ft_analyse_logic_node(node, lexer);
	else if (ft_is_subshell_node(content))
		ft_analyse_subshell_node(node, lexer);
	else if (ft_is_pipe_node(content))
		ft_analyse_pipe_node(node, lexer);
	else if (ft_is_redirect_node(content))
		ft_analyse_redirect_node(node);
	else if (content->type == AST_NODE_CMD)
		ft_analyse_cmd_node(node, lexer);
	if (node->left)
		ft_analyse_tree_nodes(node->left, lexer);
	if (node->right)
		ft_analyse_tree_nodes(node->right, lexer);
}
