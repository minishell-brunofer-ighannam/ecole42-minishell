/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:52:24 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 11:18:35 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapper_internal.h"

char	*ft_get_next_heredoc_file(t_binary_tree_node *node)
{
	char		*file;
	t_ast_node	*ast_node;
	t_exec		*exec;

	ast_node = (t_ast_node *)(node->content);
	exec = *(t_exec **)(ast_node->exec);
	file = ft_strdup((char *)exec->heredoc_files->last->content);
	exec->heredoc_files->remove(exec->heredoc_files,
		exec->heredoc_files->last, ft_free_heredoc_file_item);
	return (file);
}

void	ft_free_heredoc_file_item(void *arg)
{
	char	*file;

	file = (char *)arg;
	free(file);
}
