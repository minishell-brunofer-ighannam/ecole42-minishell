/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:58:00 by valero            #+#    #+#             */
/*   Updated: 2025/12/11 11:10:49 by ighannam         ###   ########.fr       */
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
	char		**argv;
	int			i;

	i = 0;
	argv = NULL;
	if (!node)
		return ;
	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	if (exec)
		argv = exec->argv;
	ft_clean_array_str(argv);
	exec->argv = NULL;
}
