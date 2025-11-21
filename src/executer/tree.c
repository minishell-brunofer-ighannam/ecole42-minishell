/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:40:23 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/21 16:08:58 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_execute_tree(t_node *node)
{
	int ret;

	ret = ft_execute_heredocs(node); //primeiro percorrer toda a árvore e tratar todos os heredocs. Se algum der errado, nem executa mais nada.
	if (ret != 0)
	{
		ft_set(node->ht_env, ft_strjoin("?=", ft_itoa(ret)));
		return (1);
	}
	ret = ft_execute_node(node);
	return (0);
}

int ft_execute_node(t_node *node)
{
	int ret;

	if (ft_is_redirect(node) == 1)
	{
		node->redirect = ft_new_linkedlist();
		ret = ft_visit_redirect(node);
	}
	if (node->type == NODE_CMD)
		ret = ft_execute_cmd(node);
	if (node->type == NODE_PIPE)
		ret = ft_execute_pipe(node);
	if (node->type == NODE_AND)
		ret = ft_execute_and(node);
	if (node->type == NODE_OR)
		ret = ft_execute_or(node);
	
	if (ret != 0)
	{
		ft_set(node->ht_env, ft_strjoin("?=", ft_itoa(ret)));
	}
	return (0);
}


