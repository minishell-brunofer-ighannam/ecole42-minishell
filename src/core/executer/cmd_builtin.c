/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:44:23 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/15 10:40:56 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static int	ft_execute_builtin_aux(t_binary_tree_node *node, t_ast *ast);

int	ft_execute_builtin(t_binary_tree_node *node, t_ast *ast)
{
	if (ft_strcmp(ft_get_argv(node)[0], "env") == 0)
		ft_env(ft_get_ht_env(node));
	else if (ft_strcmp(ft_get_argv(node)[0], "unset") == 0)
	{
		if (ft_get_tokens(node)[1])
			ft_unset(ft_get_ht_env(node), ft_get_tokens(node)[1]->value);
		else
			ft_unset(ft_get_ht_env(node), NULL);
	}
	else if (ft_strcmp(ft_get_argv(node)[0], "echo") == 0)
		ft_echo(node);
	else
		return (ft_execute_builtin_aux(node, ast));
	return (0);
}

static int	ft_execute_builtin_aux(t_binary_tree_node *node, t_ast *ast)
{
	if (ft_strcmp(ft_get_argv(node)[0], "export") == 0)
	{
		if (ft_get_tokens(node)[1])
			return (ft_export(ft_get_ht_env(node),
					ft_get_tokens(node)));
		else
			return (ft_export(ft_get_ht_env(node), NULL));
	}
	else if (ft_strcmp(ft_get_argv(node)[0], "pwd") == 0)
		return (ft_pwd(node));
	else if (ft_strcmp(ft_get_argv(node)[0], "exit") == 0)
		return (ft_exit(node, ast));
	else if (ft_strcmp(ft_get_argv(node)[0], "cd") == 0)
		return (ft_cd(node));
	return (0);
}
