/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:25:32 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 18:33:50 by valero           ###   ########.fr       */
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
	else if (ft_is_pipe_node(content))
		ft_analyse_pipe_node(node, lexer);
	else if (ft_is_redirect_node(content))
		ft_analyse_redirect_node(node);
	if (node->left)
		ft_analyse_tree_nodes(node->left, lexer);
	if (node->right)
		ft_analyse_tree_nodes(node->right, lexer);
}
