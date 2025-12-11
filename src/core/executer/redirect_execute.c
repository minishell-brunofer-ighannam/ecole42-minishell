/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:43:14 by valero            #+#    #+#             */
/*   Updated: 2025/12/11 15:43:28 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static int	ft_execute_redirect_in(t_linkedlist_node *node);
static int	ft_execute_redirect_out(t_linkedlist_node *node);
static int	ft_execute_append_out(t_linkedlist_node *node);
static int	ft_execute_redirect_node(t_linkedlist_node **node_redir, int *size);

int	ft_execute_redirect(t_binary_tree_node *node)
{
	t_linkedlist_node	*node_redir;
	t_linkedlist		**list_redir;
	int					size;
	int					ret;

	if (!(*ft_get_list_redirects(node)))
		return (0);
	list_redir = ft_get_list_redirects(node);
	size = (*list_redir)->size;
	node_redir = (*ft_get_list_redirects(node))->last;
	while (size > 0)
	{
		ret = ft_execute_redirect_node(&node_redir, &size);
		if (ret)
			return (ret);
	}
	return (0);
}

static int	ft_execute_redirect_node(t_linkedlist_node **node_redir, int *size)
{
	int			ret;
	t_redirect	*content;

	ret = 0;
	content = (t_redirect *)((*node_redir)->content);
	if (content->type == AST_NODE_REDIRECT_IN
		|| content->type == AST_NODE_HERE_DOC_IN)
		ret = ft_execute_redirect_in(*node_redir);
	else if (content->type == AST_NODE_REDIRECT_OUT)
		ret = ft_execute_redirect_out(*node_redir);
	else if (content->type == AST_NODE_APPEND_OUT)
		ret = ft_execute_append_out(*node_redir);
	if (ret != 0)
		return (ret);
	*node_redir = (*node_redir)->prev;
	(*size)--;
	return (ret);
}

static int	ft_execute_redirect_in(t_linkedlist_node *node)
{
	int			file;
	t_redirect	*content;

	content = (t_redirect *)(node->content);
	if (content->flag_redir_problem || (content->file && !*content->file))
	{
		ft_print_ambiguous(content);
		return (1);
	}
	file = open(content->file, O_RDONLY);
	if (file == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(content->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	return (0);
}

static int	ft_execute_redirect_out(t_linkedlist_node *node)
{
	int			file;
	t_redirect	*content;

	content = (t_redirect *)(node->content);
	if (content->flag_redir_problem || (content->file && !*content->file))
	{
		ft_print_ambiguous(content);
		return (1);
	}
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

static int	ft_execute_append_out(t_linkedlist_node *node)
{
	int			file;
	t_redirect	*content;

	content = (t_redirect *)(node->content);
	if (content->flag_redir_problem || (content->file && !*content->file))
	{
		ft_print_ambiguous(content);
		return (1);
	}
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
