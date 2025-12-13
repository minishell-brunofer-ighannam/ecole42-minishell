/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:18:47 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/13 11:57:23 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_executer(const char *line, void *exec)
{
	t_expander_callbacks	callbacks;
	t_ast					*ast;
	t_exec					**exec_ref;
	int						status;

	status = 0;
	exec_ref = exec;
	if (ft_get_sig() == SIGINT)
	{
		ft_set((*exec_ref)->ht_env, "?=130");
		ft_set_sig(0);
	}
	callbacks = ft_create_expander_callbacks(ft_expand_var, ft_expand_glob);
	ast = ft_parser(line, callbacks, exec_ref, free_ast_node);
	if (!ast)
	{
		ft_set((*exec_ref)->ht_env, "?=2");
		return (2);
	}
	status = ft_execute_tree(ast);
	return (status);
}
