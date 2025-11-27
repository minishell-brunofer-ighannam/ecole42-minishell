/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:44:23 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/26 14:18:12 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_execute_builtin(t_node *node)
{
	//ver como trataremos o fato do export e env serem "sem opções" segundo o PDF. Onde verificaremos isso?
	if (ft_strcmp(node->token[0]->value, "export") == 0) 
	{
		if (node->token[1])
			ft_export(node->ht_env, node->token[1]->value);
		else
			ft_export(node->ht_env, NULL);
	}
	else if (ft_strcmp(node->token[0]->value, "env") == 0)
		ft_env(node->ht_env);
	else if (ft_strcmp(node->token[0]->value, "set") == 0)
		ft_set(node->ht_env, node->token[1]->value);
	else if (ft_strcmp(node->token[0]->value, "unset") == 0)
	{
		if (node->token[1])
			ft_unset(node->ht_env, node->token[1]->value);
		else
			ft_unset(node->ht_env, NULL);
	}
	else if (ft_strcmp(node->token[0]->value, "cd") == 0)
		return (ft_cd(node));
	else if (ft_strcmp(node->token[0]->value, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(node->token[0]->value, "echo") == 0)
		ft_echo(node);
	return (0);
}

