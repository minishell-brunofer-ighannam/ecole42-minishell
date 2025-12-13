/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:53:43 by valero            #+#    #+#             */
/*   Updated: 2025/12/13 15:30:19 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapper_internal.h"

int	ft_get_fd_in(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	return (exec->fds[0]);
}

int	ft_get_fd_out(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	return (exec->fds[1]);
}

void	ft_close_fds(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	close(exec->fds[0]);
	close(exec->fds[1]);
	if (exec->fd_out_pipe != -1)
		close(exec->fd_out_pipe);
}

void	ft_set_fd_out_pipe(t_binary_tree_node *node, int fd)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	exec->fd_out_pipe = dup(fd);
	close(fd);
}

int ft_get_fd_out_pipe(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	return (exec->fd_out_pipe);
}
