/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:51:39 by valero            #+#    #+#             */
/*   Updated: 2025/12/08 11:38:26 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_build_internal.h"

static void	ft_push_subshell(t_buid_ast_context *ctx, void *exec);

void	ft_push_cmd_node(t_buid_ast_context *ctx, void *exec)
{
	t_ast_node			*ast_node;
	t_binary_tree		*tree;

	tree = ctx->ast->tree;
	if (ctx->prev_subset->tokens[0]->type == TOKEN_PAREN_OPEN)
		ft_push_subshell(ctx, exec);
	else
	{
		ast_node = ft_create_ast_node(
				ctx->prev_subset->tokens, AST_NODE_CMD, exec);
		tree->push_content(tree, ctx->tree_node, ctx->on_left, ast_node);
	}
}

static void	ft_push_subshell(t_buid_ast_context *ctx, void *exec)
{
	t_lexer_subset		*subset;
	t_binary_tree_node	*next_node;
	t_ast_node			*ast_node;
	t_buid_ast_context	next_ctx;
	t_binary_tree		*tree;

	tree = ctx->ast->tree;
	subset = ctx->prev_subset->subset(ctx->prev_subset, 0, 0);
	ast_node = ft_create_ast_node(subset->tokens, AST_NODE_SUBSHELL, exec);
	subset->destroy(&subset);
	tree->push_content(tree, ctx->tree_node, ctx->on_left, ast_node);
	next_node = ft_get_next_node(ctx->ast, ctx->tree_node, ctx->on_left);
	subset = ctx->prev_subset->subset(
			ctx->prev_subset, 1, ctx->prev_subset->size - 2);
	next_ctx = ft_create_buid_ast_context(
			ctx->ast, next_node, true, subset);
	ft_build_ast_node(&next_ctx, exec);
	if (subset)
		subset->destroy(&subset);
}
