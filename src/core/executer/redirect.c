/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:39:08 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/08 21:23:13 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

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
		content->file = (char *)ft_get_tokens(node)[1]->last_build->token_expanded;
	content->type = ft_get_type(node);
	ft_push_redirect(node, content);
	if (!node->left)
		return (ft_execute_redirect(node));
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

int	ft_execute_redirect(t_binary_tree_node *node)
{
	t_linkedlist_node	*node_redir;
	t_linkedlist		**list_redir;
	int					size;
	int					ret;
	t_redirect			*content;

	if (!(*ft_get_list_redirects(node)))
		return (0);
	list_redir = ft_get_list_redirects(node);
	size = (*list_redir)->size;
	node_redir = (*ft_get_list_redirects(node))->last;
	while (size > 0)
	{
		content = (t_redirect *)(node_redir->content);
		if (content->type == AST_NODE_REDIRECT_IN
			|| content->type == AST_NODE_HERE_DOC_IN)
			ret = ft_execute_redirect_in(node_redir);
		else if (content->type == AST_NODE_REDIRECT_OUT)
			ret = ft_execute_redirect_out(node_redir);
		else if (content->type == AST_NODE_APPEND_OUT)
			ret = ft_execute_append_out(node_redir);
		if (ret != 0)
			return (ret);
		node_redir = node_redir->prev;
		size--;
	}
	return (0);
}

int	ft_execute_redirect_in(t_linkedlist_node *node)
{
	int			file;
	t_redirect	*content;

	content = (t_redirect *)(node->content);
	file = open(content->file, O_RDONLY);
	if (file == -1)
	{
		perror("open");
		return (1);
	}
	dup2(file, STDIN_FILENO);
	if (content->type == AST_NODE_HERE_DOC_IN)
		unlink(content->file);
	close(file);
	return (0);
}

int	ft_execute_redirect_out(t_linkedlist_node *node)
{
	int			file;
	t_redirect	*content;

	content = (t_redirect *)(node->content);
	file = open(content->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file == -1)
	{
		perror("open");
		return (1);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (0);
}

int	ft_execute_append_out(t_linkedlist_node *node)
{
	int			file;
	t_redirect	*content;

	content = (t_redirect *)(node->content);
	file = open(content->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (file == -1)
	{
		perror("open");
		return (1);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
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
