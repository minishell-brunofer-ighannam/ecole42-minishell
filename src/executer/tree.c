/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:40:23 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/22 11:19:13 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_execute_tree(t_node *node)
{
	int ret;
	char *key_value;

	ret = ft_execute_heredocs(node); //primeiro percorrer toda a árvore e tratar todos os heredocs. Se algum der errado, nem executa mais nada.
	if (ret != 0)
	{
		key_value = ft_strjoin("?=", ft_itoa(ret));
		ft_set(node->ht_env, key_value);
		free(key_value);
		return (1);
	}
	ret = ft_execute_node(node);
	key_value = ft_strjoin("?=", ft_itoa(ret));
	ft_set(node->ht_env, key_value);
	free(key_value);
	return (ret);
}

int ft_execute_node(t_node *node)
{
	int ret;

	ret = 0;
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
	ft_set(node->ht_env, ft_strjoin("?=", ft_itoa(ret)));
	return (ret);
}


