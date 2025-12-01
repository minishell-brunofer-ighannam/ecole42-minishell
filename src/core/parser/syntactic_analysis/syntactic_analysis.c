/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:25:32 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 16:35:19 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntactic_analysis_internal.h"

static void	ft_analyse_tree_nodes(t_binary_tree_node *node);

void	ft_syntactic_analysis(t_ast *ast)
{
	if (!ast || !ast->lexer || !ast->tree || !ast->tree->root)
		return ;
	ft_analyse_tree_nodes(ast->tree->root);
}

static void	ft_analyse_tree_nodes(t_binary_tree_node *node)
{
	t_ast_node	*content;

	if (!node || !node->content)
		return ;
	content = node->content;
	if (ft_is_logic_node(content))
		ft_analyse_logic_node(node);
	else if (ft_is_pipe_node(content))
		ft_analyse_pipe_node(node);
	else if (ft_is_redirect_node(content))
		ft_analyse_redirect_node(node);
	if (node->left)
		ft_analyse_tree_nodes(node->left);
	if (node->right)
		ft_analyse_tree_nodes(node->right);
}
