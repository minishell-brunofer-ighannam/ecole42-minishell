/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:58:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/27 18:06:02 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static void					ft_build_ast_node(
								t_buid_ast_params *ctx,
								void *exec);
static void					ft_push_cmd_node(
								t_buid_ast_params *ctx,
								void *exec);
static void					ft_push_node_composition(
								int sep_idx,
								t_ast_node_type type,
								t_buid_ast_params *ctx,
								void *exec);
static void					ft_push_redirect_node(
								int sep_idx,
								t_ast_node_type type,
								t_buid_ast_params *ctx,
								void *exec);
static t_binary_tree_node	*ft_get_next_node(
								t_ast *ast,
								t_binary_tree_node *tree_node,
								bool on_left);
static t_buid_ast_params	ft_create_buid_ast_context(
								t_ast *ast,
								t_binary_tree_node *tree_node,
								bool on_left,
								t_lexer_subset *prev_subset);
static void					ft_manage_multiples_redirect(
								t_buid_ast_params *ctx,
								int *lower_precedence);
static void					ft_reorganize_redirect_write(
								t_buid_ast_params *ctx,
								t_linkedlist *list_cmd,
								t_linkedlist	*list_redir);

t_ast	*ft_ast_build(t_lexer *lexer, void *exec)
{
	t_lexer_subset		*subset;
	t_ast				*ast;
	t_buid_ast_params	next_context;

	ast = ft_create_ast(lexer);
	subset = ft_create_lexer_subset(lexer, 0, lexer->size - 1);
	next_context = ft_create_buid_ast_context(
			ast, ast->tree->root, true, subset);
	ft_build_ast_node(&next_context, exec);
	if (subset)
		subset->destroy(&subset);
	return (ast);
}

static void	ft_build_ast_node(
				t_buid_ast_params *ctx, void *exec)
{
	int					lower_precedence;
	t_ast_node_type		type;
	t_buid_ast_params	next_context;

	if (!ctx || !ctx->prev_subset)
		return ;
	next_context = ft_create_buid_ast_context(
			ctx->ast, ctx->tree_node, ctx->on_left, ctx->prev_subset);
	lower_precedence = ft_find_lower_precedence(ctx->prev_subset->tokens);
	if (lower_precedence > 0
		&& ft_is_redirect_node(ctx->prev_subset->tokens[lower_precedence]))
		ft_manage_multiples_redirect(ctx, &lower_precedence);
	if (lower_precedence < 0)
		return (ft_push_cmd_node(&next_context, exec));
	type = (int)ctx->prev_subset->tokens[lower_precedence]->type;
	if (ft_is_redirect_node(ctx->prev_subset->tokens[lower_precedence]))
		ft_push_redirect_node(lower_precedence, type, &next_context, exec);
	else
		ft_push_node_composition(lower_precedence, type, &next_context, exec);
}

static void	ft_manage_multiples_redirect(
				t_buid_ast_params *ctx,
				int *lower_precedence)
{
	t_linkedlist	*list_cmd;
	t_linkedlist	*list_redir;
	t_token			**tokens;
	int				idx;

	tokens = ctx->prev_subset->tokens;
	list_cmd = ft_new_linkedlist();
	list_redir = ft_new_linkedlist();
	idx = -1;
	while (tokens[++idx])
	{
		if (ft_is_redirect_node(tokens[idx]))
		{
			list_redir->push(list_redir, tokens[idx]);
			if (tokens[idx + 1])
				list_redir->push(list_redir, tokens[++idx]);
		}
		else
			list_cmd->push(list_cmd, tokens[idx]);
	}
	ft_reorganize_redirect_write(ctx, list_cmd, list_redir);
	*lower_precedence = ft_find_lower_precedence(ctx->prev_subset->tokens);
	list_cmd->destroy(&list_cmd, NULL);
	list_redir->destroy(&list_redir, NULL);
}

static void	ft_reorganize_redirect_write(
				t_buid_ast_params *ctx,
				t_linkedlist *list_cmd,
				t_linkedlist *list_redir)
{
	int					idx;
	t_linkedlist_node	*cmd_node;
	t_linkedlist_node	*redir_node;

	cmd_node = list_cmd->first;
	redir_node = list_redir->first;
	idx = -1;
	while (ctx->prev_subset->tokens[++idx])
	{
		while (cmd_node)
		{
			ctx->prev_subset->tokens[idx++] = cmd_node->content;
			cmd_node = cmd_node->next;
		}
		while (redir_node)
		{
			ctx->prev_subset->tokens[idx++] = redir_node->content;
			redir_node = redir_node->next;
		}
	}
}

static void	ft_push_cmd_node(t_buid_ast_params *ctx, void *exec)
{
	t_lexer_subset		*subset;
	t_binary_tree_node	*next_node;
	t_ast_node			*ast_node;
	t_buid_ast_params	next_ctx;
	t_binary_tree		*tree;

	tree = ctx->ast->tree;
	if (ctx->prev_subset->tokens[0]->type == TOKEN_PAREN_OPEN)
	{
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
	else
	{
		ast_node = ft_create_ast_node(
				ctx->prev_subset->tokens, AST_NODE_CMD, exec);
		tree->push_content(tree, ctx->tree_node, ctx->on_left, ast_node);
	}
}

static void	ft_push_node_composition(
				int sep_idx,
				t_ast_node_type type,
				t_buid_ast_params *ctx,
				void *exec)
{
	t_lexer_subset		*subset_left;
	t_lexer_subset		*subset_right;
	t_binary_tree_node	*next_node;
	t_buid_ast_params	next_context;
	t_binary_tree		*tree;

	tree = ctx->ast->tree;
	subset_left = ctx->prev_subset->subset(ctx->prev_subset, sep_idx, sep_idx);
	tree->push_content(tree, ctx->tree_node, ctx->on_left,
		ft_create_ast_node(subset_left->tokens, type, exec));
	subset_left->destroy(&subset_left);
	subset_left = ctx->prev_subset->subset(ctx->prev_subset, 0, sep_idx - 1);
	subset_right = ctx->prev_subset->subset(ctx->prev_subset, sep_idx + 1, ctx->prev_subset->size - 1);
	next_node = ft_get_next_node(ctx->ast, ctx->tree_node, ctx->on_left);
	next_context = ft_create_buid_ast_context(ctx->ast, next_node, true, subset_left);
	ft_build_ast_node(&next_context, exec);
	next_context = ft_create_buid_ast_context(ctx->ast, next_node, false, subset_right);
	ft_build_ast_node(&next_context, exec);
	if (subset_left)
		subset_left->destroy(&subset_left);
	if (subset_right)
		subset_right->destroy(&subset_right);
}

static void	ft_push_redirect_node(
				int sep_idx,
				t_ast_node_type type,
				t_buid_ast_params *ctx,
				void *exec)
{
	t_lexer_subset		*subset_left;
	t_lexer_subset		*subset_right;
	t_binary_tree_node	*next_node;
	t_buid_ast_params	next_context;
	t_binary_tree		*tree;

	tree = ctx->ast->tree;
	subset_left = ctx->prev_subset->subset(ctx->prev_subset, sep_idx, sep_idx + 1);
	tree->push_content(tree, ctx->tree_node, ctx->on_left,
		ft_create_ast_node(subset_left->tokens, type, exec));
	subset_left->destroy(&subset_left);
	subset_left = ctx->prev_subset->subset(ctx->prev_subset, 0, sep_idx - 1);
	subset_right = ctx->prev_subset->subset(
			ctx->prev_subset, sep_idx + 2, ctx->prev_subset->size - 1);
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

static t_binary_tree_node	*ft_get_next_node(
								t_ast *ast,
								t_binary_tree_node *tree_node,
								bool on_left)
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

static t_buid_ast_params	ft_create_buid_ast_context(
								t_ast *ast,
								t_binary_tree_node *tree_node,
								bool on_left,
								t_lexer_subset *prev_subset)
{
	t_buid_ast_params	params;

	params.ast = ast;
	params.tree_node = tree_node;
	params.on_left = on_left;
	params.prev_subset = prev_subset;
	return (params);
}
