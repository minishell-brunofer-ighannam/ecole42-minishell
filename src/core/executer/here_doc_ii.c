/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_ii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:39:37 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/28 16:42:18 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char			*ft_generate_temp_file(void);
void			ft_dfs_find_heredoc(t_linkedlist *heredoc, t_node *node);
t_linkedlist	*ft_find_all_heredoc(t_node *node);

char	*ft_generate_temp_file(void)
{
	int		hd;
	char	*file;
	char	*num;

	hd = 0;
	while (hd < INT_MAX)
	{
		num = ft_itoa(hd);
		if (!num)
			return (NULL);
		file = ft_strjoin("/tmp/minishell_hd_", num);
		free(num);
		if (!file)
			return (NULL);
		if (access(file, F_OK) == -1)
			return (file);
		free(file);
		hd++;
	}
	return (NULL);
}

t_linkedlist	*ft_find_all_heredoc(t_node *node)
{
	t_linkedlist	*heredoc;

	heredoc = ft_new_linkedlist();
	ft_dfs_find_heredoc(heredoc, node);
	return (heredoc);
}

void	ft_dfs_find_heredoc(t_linkedlist *heredoc, t_node *node) // dfs = Depth-First Search — Busca em Profundidade
{
	if (!node)
		return ;
	if (node->type == NODE_HERE_DOC_IN)
		heredoc->push(heredoc, node);
	ft_dfs_find_heredoc(heredoc, node->left);
	ft_dfs_find_heredoc(heredoc, node->right);
}