/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_redirect_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:19:40 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 16:33:09 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntactic_analysis_internal.h"

static void	ft_analyse_adjacent_tokens(t_token *right_token);

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
	ft_analyse_adjacent_tokens(content->tokens[1]);
}

static void	ft_analyse_adjacent_tokens(t_token *right_token)
{
	if (!right_token)
		return ;
	if (ft_is_reserved_token(right_token)
		|| right_token->type == TOKEN_PAREN_CLOSE
		|| right_token->type == TOKEN_PAREN_OPEN)
		right_token->sintaxe_error = true;
}
