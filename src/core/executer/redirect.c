/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:39:08 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/08 21:47:42 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static int	ft_visit_redirect_recursively(t_binary_tree_node *node, t_ast *ast);

int	ft_is_redirect(t_binary_tree_node *node)
{
	return (ft_get_type(node) == AST_NODE_REDIRECT_IN
		|| ft_get_type(node) == AST_NODE_REDIRECT_OUT
		|| ft_get_type(node) == AST_NODE_APPEND_OUT
		|| ft_get_type(node) == AST_NODE_HERE_DOC_IN);
}

int	ft_visit_redirect(t_binary_tree_node *node, t_ast *ast)
{
	t_redirect	*content;

	ft_expand_tokens(node);
	content = ft_calloc(1, sizeof(t_redirect));
	if (ft_get_type(node) == AST_NODE_HERE_DOC_IN)
	{
		content->file = ft_get_next_heredoc_file(node);
		ft_free_argv(node);
	}
	else
		content->file = ft_get_tokens(node)[1]->last_build->token_expanded;
	content->type = ft_get_type(node);
	ft_push_redirect(node, content);
	if (!node->left)
		return (ft_execute_redirect(node));
	return (ft_visit_redirect_recursively(node, ast));
}

static int	ft_visit_redirect_recursively(t_binary_tree_node *node, t_ast *ast)
{
	if (ft_is_redirect(node->left) == 1)
	{
		ft_set_redirect(node->left, *ft_get_list_redirects(node));
		return (ft_visit_redirect(node->left, ast));
	}
	if (ft_get_type(node->left) == AST_NODE_SUBSHELL)
	{
		ft_execute_redirect(node);
		return (ft_execute_subshell(node->left, ast));
	}
	if (ft_is_redirect(node->left) == 0)
	{
		ft_set_redirect(node->left, *ft_get_list_redirects(node));
		return (ft_execute_node(node->left, ast));
	}
	return (0);
}

void	ft_free_item_redirect(void *content)
{
	t_redirect	*content_redirect;

	if (!content)
		return ;
	content_redirect = (t_redirect *)content;
	if (content_redirect->type == AST_NODE_HERE_DOC_IN)
		free(content_redirect->file);
	content_redirect->type = AST_NODE_UNKNOWN;
	content_redirect->file = NULL;
	free(content_redirect);
	content_redirect = NULL;
}
