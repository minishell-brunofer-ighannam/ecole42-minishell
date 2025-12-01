/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:58:48 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 13:29:42 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_build_internal.h"

t_ast	*ft_ast_build(t_lexer *lexer, void *exec)
{
	t_lexer_subset		*subset;
	t_ast				*ast;
	t_buid_ast_context	next_context;

	ast = ft_create_ast(lexer);
	subset = ft_create_lexer_subset(lexer, 0, lexer->size - 1);
	next_context = ft_create_buid_ast_context(
			ast, ast->tree->root, true, subset);
	ft_build_ast_node(&next_context, exec);
	if (subset)
		subset->destroy(&subset);
	return (ast);
}

void	ft_build_ast_node(t_buid_ast_context *ctx, void *exec)
{
	int					lower_precedence;
	t_ast_node_type		type;
	t_buid_ast_context	next_context;

	if (!ctx || !ctx->prev_subset)
		return ;
	next_context = ft_create_buid_ast_context(
			ctx->ast, ctx->tree_node, ctx->on_left, ctx->prev_subset);
	lower_precedence = ft_find_lower_precedence(ctx->prev_subset->tokens);
	if (lower_precedence > 0
		&& ft_is_redirect_token(ctx->prev_subset->tokens[lower_precedence]))
		ft_manage_multiples_redirect(ctx, &lower_precedence);
	if (lower_precedence < 0)
		return (ft_push_cmd_node(&next_context, exec));
	type = (int)ctx->prev_subset->tokens[lower_precedence]->type;
	if (ft_is_redirect_token(ctx->prev_subset->tokens[lower_precedence]))
		ft_push_redirect_node(lower_precedence, type, &next_context, exec);
	else
		ft_push_node_composition(lower_precedence, type, &next_context, exec);
}
