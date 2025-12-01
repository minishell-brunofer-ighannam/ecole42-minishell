/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:40:23 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/01 15:53:58 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_execute_tree(t_binary_tree_node *node)
{
	int ret;
	char *key_value;

	ret = ft_execute_heredocs(node); //primeiro percorrer toda a árvore e tratar todos os heredocs. Se algum der errado (ctrl C), nem executa mais nada.
	if (ret != 0)
	{
		key_value = ft_strjoin("?=", ft_itoa(ret));
		ft_set(ft_get_ht_env(node), key_value);
		free(key_value);
		return (1);
	}
	ret = ft_execute_node(node);
	key_value = ft_strjoin("?=", ft_itoa(ret));
	ft_set(ft_get_ht_env(node), key_value);
	free(key_value);
	return (ret);
}

int ft_execute_node(t_binary_tree_node *node)
{
	int ret;

	ret = 0;
	if (ft_is_redirect(node) == 1)
	{
		ft_init_redirect(node);
		ret = ft_visit_redirect(node);
	}
	if (ft_get_type(node) == AST_NODE_CMD)
		ret = ft_execute_cmd(node);
	if (ft_get_type(node) == AST_NODE_PIPE)
		ret = ft_execute_pipe(node);
	if (ft_get_type(node) == AST_NODE_AND)
		ret = ft_execute_and(node);
	if (ft_get_type(node) == AST_NODE_OR)
		ret = ft_execute_or(node);
	if (ft_get_type(node) == AST_NODE_SUBSHELL)
		ret = ft_execute_subshell(node);
	ft_set(ft_get_ht_env(node), ft_strjoin("?=", ft_itoa(ret)));
	return (ret);
}


