/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:27:42 by valero            #+#    #+#             */
/*   Updated: 2025/12/08 11:40:26 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_build_internal.h"

static void	ft_reorganize_redirect_write(
				t_buid_ast_context *ctx,
				t_linkedlist *list_cmd,
				t_linkedlist *list_redir);

void	ft_push_redirect_node(int sep_idx, t_ast_node_type type,
			t_buid_ast_context *ctx, void *exec)
{
	t_lexer_subset		*sub_left;
	t_lexer_subset		*sub_right;
	t_binary_tree_node	*next_node;
	t_buid_ast_context	next_context;
	t_binary_tree		*tree;

	tree = ctx->ast->tree;
	sub_left = ctx->prev_subset->subset(ctx->prev_subset, sep_idx, sep_idx + 1);
	tree->push_content(tree, ctx->tree_node, ctx->on_left,
		ft_create_ast_node(sub_left->tokens, type, exec));
	sub_left->destroy(&sub_left);
	sub_left = ctx->prev_subset->subset(ctx->prev_subset, 0, sep_idx - 1);
	sub_right = ctx->prev_subset->subset(
			ctx->prev_subset, sep_idx + 2, ctx->prev_subset->size - 1);
	next_node = ft_get_next_node(ctx->ast, ctx->tree_node, ctx->on_left);
	next_context = ft_create_buid_ast_context(
			ctx->ast, next_node, true, sub_left);
	ft_build_ast_node(&next_context, exec);
	next_context = ft_create_buid_ast_context(
			ctx->ast, next_node, !sub_left, sub_right);
	ft_build_ast_node(&next_context, exec);
	if (sub_left)
		sub_left->destroy(&sub_left);
	if (sub_right)
		sub_right->destroy(&sub_right);
}

void	ft_manage_multiples_redirect(
				t_buid_ast_context *ctx,
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
		if (ft_is_redirect_token(tokens[idx]))
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
				t_buid_ast_context *ctx,
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
		while (ctx->prev_subset->tokens[idx] && cmd_node)
		{
			ctx->prev_subset->tokens[idx++] = cmd_node->content;
			cmd_node = cmd_node->next;
		}
		while (ctx->prev_subset->tokens[idx] && redir_node)
		{
			ctx->prev_subset->tokens[idx++] = redir_node->content;
			redir_node = redir_node->next;
		}
		if (!ctx->prev_subset->tokens[idx])
			break ;
	}
}
