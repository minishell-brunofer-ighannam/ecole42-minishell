/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ii.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 22:12:11 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/09 12:25:50 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_expand_tokens(t_binary_tree_node *node)
{
	t_token				**token;
	int					i;
	t_expansion_build	*build;

	i = 0;
	token = ft_get_tokens(node);
	while (token[i])
	{
		build = token[i]->build_expansion(token[i], ft_get_ht_env(node));
		build->destroy(&build);
		i++;
	}
	return (i);
}

void	ft_built_args(t_binary_tree_node *node)
{
	t_token	**token;
	int		i;
	int		j;

	ft_init_argv(node, ft_expand_tokens(node) + 1);
	i = 0;
	j = 0;
	token = ft_get_tokens(node);
	while (token[i])
	{
		if (token[i]->last_build->token_expanded[0] != '\0')
		{
			ft_set_argv(node, j, token[i]->last_build->token_expanded);
			j++;
		}
		i++;
	}
}

void	ft_print_error_cmd(int error, char *path)
{
	if (error == EACCES)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	if (error == ENOENT)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	if (error == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	}
	if (error == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
}

void	ft_destroy_tree_cmd(char *path, t_binary_tree_node *node,
		t_ast *ast)
{
	free(path);
	ft_free_argv(node);
	ft_set_flag_destroy_exec(node);
	ast->destroy(&ast, free_ast_node);
}
