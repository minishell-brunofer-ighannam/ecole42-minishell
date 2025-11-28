/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:49:25 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/28 16:43:59 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"


static int			ft_process_heredoc(t_linkedlist_node *item_list);

static int	ft_read_line_heredoc(int fd, const char *delimit, int is_expandable, t_node *node);

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
	int is_expandable;

	file = ft_generate_temp_file();
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	node = (t_node *)item_list->content;
	delimit = node->token[1]->value;
	if (ft_strcmp(delimit, node->token[1]->value) == 0)
		is_expandable = 1;
	else
		is_expandable = 0;
	if (ft_read_line_heredoc(fd, delimit, is_expandable, node) != 0) // tratamento para se der problema(ex.: ctrl-C)
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

static int	ft_read_line_heredoc(int fd, const char *delimit, int is_expandable, t_node *node)
{
	char	*line;
	//t_token *token;
	(void)node;

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
		if (is_expandable == 1)
		{
			// token = ft_tokenize(line, 0, NULL, );
			// token->build_expansion(token, node->ht_env);
			// ft_putendl_fd(token->last_build->token_expanded, fd);
			ft_putendl_fd(line, fd);
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}




