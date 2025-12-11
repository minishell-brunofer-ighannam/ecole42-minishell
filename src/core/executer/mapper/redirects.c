/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:55:45 by valero            #+#    #+#             */
/*   Updated: 2025/12/11 13:44:48 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapper_internal.h"

void	ft_init_redirect(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	exec->redirect = ft_new_linkedlist();
}

t_linkedlist	**ft_get_list_redirects(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	return (&exec->redirect);
}

void	ft_set_redirect(t_binary_tree_node *node, t_linkedlist *list)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	exec->redirect = list;
}

void	ft_push_redirect(t_binary_tree_node *node, t_redirect *content)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	exec->redirect->push(exec->redirect, content);
}

void	ft_clean_redirect(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	if (exec && exec->redirect)
		exec->redirect->destroy(&exec->redirect, ft_free_item_redirect);
}
