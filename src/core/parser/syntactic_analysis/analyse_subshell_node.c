/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_subshell_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:19:40 by valero            #+#    #+#             */
/*   Updated: 2025/12/07 16:49:11 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntactic_analysis_internal.h"

static void	ft_analyse_adjacent_tokens(t_ast_node *content, t_lexer *lexer);

void	ft_analyse_subshell_node(t_binary_tree_node *node, t_lexer *lexer)
{
	t_ast_node	*content;

	if (!node)
		return ;
	content = (t_ast_node *)node->content;
	if (!ft_is_subshell_node(content))
		return ;
	if (!node->left)
	{
		ft_analyse_adjacent_tokens(content, lexer);
		return ;
	}
	ft_analyse_adjacent_tokens(content, lexer);
}

static void	ft_analyse_adjacent_tokens(t_ast_node *content, t_lexer *lexer)
{
	t_token	*right_token;

	if (!content || !lexer)
		return ;
	right_token = lexer->tokens[content->tokens[0]->position + 1];
	if (right_token->type == TOKEN_PAREN_CLOSE)
		right_token->sintaxe_error = true;
}
