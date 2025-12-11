/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_redirect_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:19:40 by valero            #+#    #+#             */
/*   Updated: 2025/12/11 12:50:46 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntactic_analysis_internal.h"

static void	ft_analyse_adjacent_tokens(
				t_token *right_token, t_binary_tree_node *left_node);

void	ft_analyse_redirect_node(t_binary_tree_node	*node)
{
	t_ast_node	*content;

	if (!node)
		return ;
	content = (t_ast_node *)node->content;
	if (!ft_is_redirect_node(content))
		return ;
	if (!content->tokens[1])
	{
		content->tokens[0]->sintaxe_error = true;
		return ;
	}
	ft_analyse_adjacent_tokens(content->tokens[1], node->left);
}

static void	ft_analyse_adjacent_tokens(
				t_token *right_token, t_binary_tree_node *left_node)
{
	t_token	*left_token;

	if (!right_token)
		return ;
	left_token = NULL;
	if (left_node)
		left_token = ((t_ast_node *)left_node->content)->tokens[0];
	if (ft_is_reserved_token(right_token)
		|| right_token->type == TOKEN_PAREN_CLOSE
		|| right_token->type == TOKEN_PAREN_OPEN)
		right_token->sintaxe_error = true;
	if (left_token && left_token->type == TOKEN_PAREN_OPEN
		&& left_token->position > right_token->position)
		left_token->sintaxe_error = true;
}
