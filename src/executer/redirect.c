/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:39:08 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/22 19:49:24 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_is_redirect(t_node *node)
{
	return (node->type == NODE_REDIRECT_IN || node->type == NODE_REDIRECT_OUT
		|| node->type == NODE_APPEND_OUT || node->type == NODE_HERE_DOC_IN);
}

int ft_visit_redirect(t_node *node)
{
	t_redirect *content;

	content = ft_calloc(1, sizeof(t_redirect));
	if (node->type == NODE_HERE_DOC_IN)
		content->file = node->argv[0];
	else
		content->file = node->token[1]->value;
	content->type = node->type;
	node->redirect->push(node->redirect, content);
	if (!node->left)
		return(ft_execute_redirect(node));
	if (ft_is_redirect(node->left) == 1)
	{
		node->left->redirect = node->redirect;
		ft_visit_redirect(node->left);
	}
	if (ft_is_redirect(node->left) == 0)
	{
		node->left->redirect = node->redirect;
		return(ft_execute_node(node->left));
	}
	if (node->left->type == NODE_SUBSHELL)
	{
		ft_execute_redirect(node);
		return(ft_execute_subshell(node->left));
	}
	//a função não deve chegar aqui. Se chegar há algum erro anterior. TIRAR PRINT ABAIXO!
	printf("ft_visit_redirect --> a função não deveria ter chegado aqui!");
	return (3);	
}

int ft_execute_redirect(t_node *node) //recebe nó com lista de redirecionamentos e executa os redirecionamentos.
{
	t_linkedlist_node *node_redir;
	int size;
	int ret;
	t_redirect *content;

	if (!(node->redirect)) //se não tem redirect para fazer, só retorna 0
		return (0);
	size = node->redirect->size;
	node_redir = node->redirect->last;
	while (size > 0)
	{
		content = (t_redirect *)(node_redir->content);
		if (content->type == NODE_REDIRECT_IN || content->type == NODE_HERE_DOC_IN)
			ret = ft_execute_redirect_in(node_redir);
		else if (content->type == NODE_REDIRECT_OUT)
			ret = ft_execute_redirect_out(node_redir);
		else if (content->type == NODE_APPEND_OUT)
			ret = ft_execute_append_out(node_redir);
		if (ret != 0)
			return (ret);
		node_redir = node_redir->prev;
		size--;
	}
	return (0);	
}

int ft_execute_redirect_in(t_linkedlist_node *node)
{
	int file;
	t_redirect *content;

	content = (t_redirect *)(node->content);
	file = open(content->file, O_RDONLY);
	if (file == -1)
	{
		perror("open");
		return (1);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	return (0);
}

int ft_execute_redirect_out(t_linkedlist_node *node)
{
	int file;
	t_redirect *content;

	content = (t_redirect *)(node->content);
	
	file = open(content->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file == -1)
	{
		perror("open");
		return (1);
	}
	dup2(file, STDOUT_FILENO);
	if (content->type == NODE_HERE_DOC_IN)
		unlink(content->file);
	close(file);
	return (0);
}

int ft_execute_append_out(t_linkedlist_node *node)
{
	int file;
	t_redirect *content;

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
