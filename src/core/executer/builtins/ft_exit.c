/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:42:13 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/11 11:10:26 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_verify_number(char *str);

int	ft_exit(t_binary_tree_node *node, t_ast *ast)
{
	int		status;
	char	*number;

	if (ft_get_tokens(node)[1]->last_build->token_expanded)
		number = ft_get_tokens(node)[1]->last_build->token_expanded;
	else
		number = ft_get_tokens(node)[1]->last_build->glob_error;
	if (!node->parent)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (ft_get_argv(node)[1] == NULL)
		status = 0;
	else if (ft_verify_number(number) == 2)
		status = 2;
	else if (ft_get_argv(node)[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else
		status = ft_atoi(ft_get_argv(node)[1]);
	ft_free_argv(node);
	ft_set_flag_destroy_exec(node);
	ast->destroy(&ast, free_ast_node);
	status = status % 256;
	exit(status);
}

static int	ft_verify_number(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '+' && str[0] != '-' && ft_isdigit(str[0]) == 0)
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
