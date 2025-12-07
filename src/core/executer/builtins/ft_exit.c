/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:42:13 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/07 16:51:16 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int ft_verify_number(char *str);

int	ft_exit(t_binary_tree_node *node, t_ast	*ast)
{
	int status;

	if (!node->parent)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (ft_get_argv(node)[1] == NULL)
		status = 0;
	else if (ft_verify_number(ft_get_argv(node)[1]) == 2)
		status = 2;
	else if (ft_get_argv(node)[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	else
		status = ft_atoi(ft_get_argv(node)[1]);
	ft_set_flag_destroy_exec(node);
	ast->destroy(&ast, free_ast_node);
	status = status % 256;
	exit(status);
}

static int ft_verify_number(char *str)
{
	int i;

	i = 1;
	if (str[0] != '+' && str[0] != '-' && ft_isdigit(str[0]) == 0 )
	{
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (2);
		i++;
	}
	return (0);
}
