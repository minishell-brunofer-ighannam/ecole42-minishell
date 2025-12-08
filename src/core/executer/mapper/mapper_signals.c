/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:31:53 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/08 20:29:52 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapper_internal.h"

int	ft_get_flag_n(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	return (exec->flag_n);
}

void	ft_set_flag_n(t_binary_tree_node *node, int flag)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	exec->flag_n = flag;
}
