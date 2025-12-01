/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_logic_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:19:40 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 17:01:13 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntactic_analysis_internal.h"

static void	ft_analyse_adjacent_tokens(
				t_ast_node *content, t_ast_node *left_content,
				t_ast_node *right_content);

void	ft_analyse_logic_node(t_binary_tree_node	*node)
{
	t_ast_node	*content;
	t_ast_node	*left_content;
	t_ast_node	*right_content;
	t_ast_node	*parent_content;

	if (!node)
		return ;
	content = (t_ast_node *)node->content;
	if (node->parent)
	{
		parent_content = (t_ast_node *)node->parent->content;
		if (ft_is_reserved_node(parent_content))
			return ;
	}
	if (!ft_is_logic_node(content))
		return ;
	if (!node->left || !node->right)
	{
		content->tokens[0]->sintaxe_error = true;
		return ;
	}
	left_content = (t_ast_node *)node->left->content;
	right_content = (t_ast_node *)node->right->content;
	ft_analyse_adjacent_tokens(content, left_content, right_content);
}

static void	ft_analyse_adjacent_tokens(
				t_ast_node *content, t_ast_node *left_content,
				t_ast_node *right_content)
{
	t_token	*left_token;
	t_token	*right_token;

	if (!content || !left_content || !right_content)
		return ;
	left_token = left_content->tokens[0];
	right_token = right_content->tokens[0];
	if (ft_is_reserved_token(left_token)
		|| left_token->type == TOKEN_PAREN_OPEN)
		content->tokens[0]->sintaxe_error = true;
	if (ft_is_logic_token(right_token)
		|| right_token->type == TOKEN_PAREN_CLOSE)
		right_content->tokens[0]->sintaxe_error = true;
}
