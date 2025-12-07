/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build_composition.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:13:13 by valero            #+#    #+#             */
/*   Updated: 2025/12/07 20:25:23 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_build_internal.h"

void	ft_push_node_composition(int sep_idx, t_ast_node_type type,
			t_buid_ast_context *ctx, void *exec)
{
	t_lexer_subset		*subset_left;
	t_lexer_subset		*subset_right;
	t_binary_tree_node	*next_node;
	t_buid_ast_context	next_context;
	t_binary_tree		*tree;

	tree = ctx->ast->tree;
	subset_left = ctx->prev_subset->subset(ctx->prev_subset, sep_idx, sep_idx);
	tree->push_content(tree, ctx->tree_node, ctx->on_left,
		ft_create_ast_node(subset_left->tokens, type, exec));
	subset_left->destroy(&subset_left);
	subset_left = ctx->prev_subset->subset(ctx->prev_subset, 0, sep_idx - 1);
	subset_right = ctx->prev_subset->subset(
			ctx->prev_subset, sep_idx + 1, ctx->prev_subset->size - 1);
	next_node = ft_get_next_node(ctx->ast, ctx->tree_node, ctx->on_left);
	next_context = ft_create_buid_ast_context(
			ctx->ast, next_node, true, subset_left);
	ft_build_ast_node(&next_context, exec);
	next_context = ft_create_buid_ast_context(
			ctx->ast, next_node, false, subset_right);
	ft_build_ast_node(&next_context, exec);
	if (subset_left)
		subset_left->destroy(&subset_left);
	if (subset_right)
		subset_right->destroy(&subset_right);
}
