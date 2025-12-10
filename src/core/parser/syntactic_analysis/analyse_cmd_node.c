/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_cmd_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:19:40 by valero            #+#    #+#             */
/*   Updated: 2025/12/10 12:19:50 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntactic_analysis_internal.h"

static void	ft_analyse_adjacent_tokens(t_ast_node *content, t_lexer *lexer);

void	ft_analyse_cmd_node(t_binary_tree_node *node, t_lexer *lexer)
{
	t_ast_node	*content;

	if (!node)
		return ;
	content = (t_ast_node *)node->content;
	if (ft_is_reserved_node(content) || ft_is_subshell_node(content))
		return ;
	if (node->left || node->right)
	{
		content->tokens[0]->sintaxe_error = true;
		return ;
	}
	ft_analyse_adjacent_tokens(content, lexer);
}

static void	ft_analyse_adjacent_tokens(t_ast_node *content, t_lexer *lexer)
{
	t_token	**tokens;
	int		i;

	if (!content || !lexer)
		return ;
	tokens = content->tokens;
	i = -1;
	while (tokens[++i])
	{
		if (tokens[i]->type == TOKEN_PAREN_OPEN)
			tokens[i]->sintaxe_error = true;
		if (tokens[i]->type == TOKEN_PAREN_CLOSE)
		{
			if (tokens[i + 1])
				tokens[i + 1]->sintaxe_error = true;
			else
				tokens[i]->sintaxe_error = true;
		}
	}
}
