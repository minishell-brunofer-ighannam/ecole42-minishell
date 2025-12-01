/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:54:04 by valero            #+#    #+#             */
/*   Updated: 2025/11/30 21:10:40 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_build_internal.h"

static int	ft_get_precedence(t_token *token);
static void	ft_jump_to_paren_closing(t_token **tokens, int *idx);

int	ft_find_lower_precedence(t_token **tokens)
{
	int	idx;
	int	lower_precedence_idx;
	int	lower_precedence;
	int	curr_precedence;

	lower_precedence_idx = -1;
	lower_precedence = 4;
	idx = -1;
	while (tokens[++idx])
	{
		if (tokens[idx]->type == TOKEN_PAREN_OPEN)
			ft_jump_to_paren_closing(tokens, &idx);
		if (!tokens[idx])
			break ;
		curr_precedence = ft_get_precedence(tokens[idx]);
		if (curr_precedence && curr_precedence <= lower_precedence)
		{
			lower_precedence = curr_precedence;
			lower_precedence_idx = idx;
		}
	}
	return (lower_precedence_idx);
}

static int	ft_get_precedence(t_token *token)
{
	int	max_precedence;

	max_precedence = 4;
	if (token->type == TOKEN_PAREN_OPEN)
		return (max_precedence - 0);
	if (ft_is_redirect_node(token))
		return (max_precedence - 1);
	if (token->type == TOKEN_PIPE)
		return (max_precedence - 2);
	if (token->type == TOKEN_AND || token->type == TOKEN_OR)
		return (max_precedence - 3);
	return (0);
}

t_binary_tree_node	*ft_get_next_node(t_ast *ast,
						t_binary_tree_node *tree_node, bool on_left)
{
	if (!tree_node)
		return (ast->tree->root);
	else
	{
		if (on_left)
			return (tree_node->left);
		return (tree_node->right);
	}
}

t_buid_ast_context	ft_create_buid_ast_context(t_ast *ast,
						t_binary_tree_node *tree_node, bool on_left,
						t_lexer_subset *prev_subset)
{
	t_buid_ast_context	context;

	context.ast = ast;
	context.tree_node = tree_node;
	context.on_left = on_left;
	context.prev_subset = prev_subset;
	return (context);
}

static void	ft_jump_to_paren_closing(t_token **tokens, int *idx)
{
	int	opened_parens;

	opened_parens = 0;
	if (tokens[(*idx)]->type == TOKEN_PAREN_OPEN)
		opened_parens++;
	while (tokens[++(*idx)] && opened_parens)
	{
		if (tokens[*idx]->type == TOKEN_PAREN_OPEN)
			opened_parens++;
		if (tokens[*idx]->type == TOKEN_PAREN_CLOSE)
			opened_parens--;
	}
}
