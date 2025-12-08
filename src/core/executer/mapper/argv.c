/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:58:00 by valero            #+#    #+#             */
/*   Updated: 2025/12/08 15:58:53 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapper_internal.h"

void	ft_init_argv(t_binary_tree_node *node, int size)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	exec->argv = ft_calloc(size + 1, sizeof(char *));
}

char	**ft_get_argv(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	return (exec->argv);
}

void	ft_set_argv(t_binary_tree_node *node, int index, char *str)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	exec->argv[index] = str;
}

void	ft_free_argv(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	if (!node)
		return ;
	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	if (exec->argv)
	{
		free(exec->argv);
		exec->argv = NULL;
	}
}
