/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:49:25 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/27 16:33:52 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void			ft_dfs_find_heredoc(t_linkedlist *heredoc, t_node *node);
static t_linkedlist	*ft_find_all_heredoc(t_node *node);
static int			ft_process_heredoc(t_linkedlist_node *item_list);
static char			*ft_generate_temp_file(void);
static int			ft_read_line_heredoc(int fd, const char *delimit);

//se o delimitador estiver entre "", ele espande o que tiver $ dentro do arquivo temporário

int	ft_execute_heredocs(t_node *node)
{
	t_linkedlist		*heredoc;
	t_linkedlist_node	*item_list;

	heredoc = ft_find_all_heredoc(node);
	item_list = heredoc->last;
	while (item_list)
	{
		if (ft_process_heredoc(item_list) != 0)
			return (130);
		item_list = item_list->prev;
	}
	return (0);
}

static int	ft_process_heredoc(t_linkedlist_node *item_list)
{
	t_node	*node;
	const char	*delimit;
	char	*file;
	int		fd;

	file = ft_generate_temp_file();
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	node = (t_node *)item_list->content;
	delimit = node->token[1]->value;
	if (ft_read_line_heredoc(fd, delimit) != 0) // tratamento para se der problema(ex.: ctrl-C)
	{
		close(fd);
		unlink(file);
		free(file);
		return (130);
	}
	close(fd);
	node->argv = ft_calloc(2, sizeof(char *));
	node->argv[0] = file;
	return (0);
}

static int	ft_read_line_heredoc(int fd, const char *delimit)
{
	char	*line;

	ft_handle_sig_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line && ft_get_sig() == SIGINT)
			return (130);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document ", 1);
			ft_putstr_fd("delimited by end-of-file (wanted `", 1);
			ft_putstr_fd(delimit, 1);
			ft_putstr_fd("')\n", 1);
			return (0);
		}
		if (ft_strcmp(line, delimit) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

static char	*ft_generate_temp_file(void)
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

static t_linkedlist	*ft_find_all_heredoc(t_node *node)
{
	t_linkedlist	*heredoc;

	heredoc = ft_new_linkedlist();
	ft_dfs_find_heredoc(heredoc, node);
	return (heredoc);
}

static void	ft_dfs_find_heredoc(t_linkedlist *heredoc, t_node *node) // dfs = Depth-First Search — Busca em Profundidade
{
	if (!node)
		return ;
	if (node->type == NODE_HERE_DOC_IN)
		heredoc->push(heredoc, node);
	ft_dfs_find_heredoc(heredoc, node->left);
	ft_dfs_find_heredoc(heredoc, node->right);
}
