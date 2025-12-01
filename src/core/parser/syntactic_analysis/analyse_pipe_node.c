/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_pipe_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:19:40 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 18:31:02 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntactic_analysis_internal.h"

static void	ft_analyse_adjacent_tokens(t_ast_node *content, t_lexer *lexer);

void	ft_analyse_pipe_node(t_binary_tree_node *node, t_lexer *lexer)
{
	t_ast_node	*content;

	if (!node)
		return ;
	content = (t_ast_node *)node->content;
	if (!ft_is_pipe_node(content))
		return ;
	if (!node->left || !node->right)
	{
		content->tokens[0]->sintaxe_error = true;
		return ;
	}
	ft_analyse_adjacent_tokens(content, lexer);
}

static void	ft_analyse_adjacent_tokens(t_ast_node *content, t_lexer *lexer)
{
	t_token	*left_token;

	if (!content || !lexer)
		return ;
	left_token = lexer->tokens[content->tokens[0]->position - 1];
	if (ft_is_reserved_token(left_token)
		|| left_token->type == TOKEN_PAREN_OPEN)
		content->tokens[0]->sintaxe_error = true;
}
