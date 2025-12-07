/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:44:23 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/07 15:05:30 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_execute_builtin(t_binary_tree_node *node, t_ast *ast)
{
	if (ft_strcmp(ft_get_tokens(node)[0]->value, "export") == 0) 
	{
		if (ft_get_tokens(node)[1])
			return (ft_export(ft_get_ht_env(node), ft_get_tokens(node)[1]->value));
		else
			return (ft_export(ft_get_ht_env(node), NULL));
	}
	else if (ft_strcmp(ft_get_tokens(node)[0]->value, "env") == 0)
		ft_env(ft_get_ht_env(node));
	else if (ft_strcmp(ft_get_tokens(node)[0]->value, "set") == 0)
		ft_set(ft_get_ht_env(node), ft_get_tokens(node)[1]->value);
	else if (ft_strcmp(ft_get_tokens(node)[0]->value, "unset") == 0)
	{
		if (ft_get_tokens(node)[1])
			ft_unset(ft_get_ht_env(node), ft_get_tokens(node)[1]->value);
		else
			ft_unset(ft_get_ht_env(node), NULL);
	}
	else if (ft_strcmp(ft_get_tokens(node)[0]->value, "cd") == 0)
		return (ft_cd(node));
	else if (ft_strcmp(ft_get_tokens(node)[0]->value, "pwd") == 0)
		return (ft_pwd(node));
	else if (ft_strcmp(ft_get_tokens(node)[0]->value, "echo") == 0)
		ft_echo(node);
	else if (ft_strcmp(ft_get_tokens(node)[0]->value, "exit") == 0)
		return (ft_exit(node, ast));
	return (0);
}

