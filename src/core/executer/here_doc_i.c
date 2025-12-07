/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:49:25 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/07 12:30:16 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static int	ft_process_heredoc(t_linkedlist_node *item_list);
static int	ft_read_line_heredoc(int fd, const char *delimit, int is_expandable,
				t_binary_tree_node *node);
//static void	ft_free_heredoc(void *arg);

int	ft_execute_heredocs(t_binary_tree_node *node)
{
	t_linkedlist		*heredoc;
	t_linkedlist_node	*item_list;

	heredoc = ft_find_all_heredoc(node);
	(*(t_exec **)(((t_ast_node *)(node->content))->exec))->heredoc = heredoc;
	(*(t_exec **)(((t_ast_node *)(node->content))->exec))->heredoc_files = ft_new_linkedlist();
	item_list = heredoc->last;
	while (item_list)
	{
		if (ft_process_heredoc(item_list) != 0)
		{
			//heredoc->destroy(&heredoc, NULL);
			return (130);
		}
		item_list = item_list->prev;
	}
	return (0);
}

// static void	ft_free_heredoc(void *arg)
// {
// 	t_linkedlist_node	*node;
// 	t_redirect			*redirect;

// 	node = (t_linkedlist_node *)arg;
// 	redirect = (t_redirect *)(node->content);
// 	free(redirect->file);
// 	redirect->file = NULL;
// }

static int	ft_process_heredoc(t_linkedlist_node *item_list)
{
	t_binary_tree_node	*node;
	char				*delimit;
	char				*file;
	int					fd;
	int					is_expandable;

	file = ft_generate_temp_file();
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	node = (t_binary_tree_node *)item_list->content;
	delimit = ft_get_tokens(node)[1]->remove_quotes(ft_get_tokens(node)[1]);
	if (ft_strcmp(delimit, ft_get_tokens(node)[1]->value) == 0)
		is_expandable = 1;
	else
		is_expandable = 0;
	if (ft_read_line_heredoc(fd, delimit, is_expandable, node) != 0)
	{
		close(fd);
		unlink(file);
		free(file);
		free(delimit);
		return (130);
	}
	close(fd);
	free(delimit);
	((*(t_exec **)(((t_ast_node *)(node->content))->exec))->heredoc_files)->push(((*(t_exec **)(((t_ast_node *)(node->content))->exec))->heredoc_files), file);
	return (0);
}

static int	ft_read_line_heredoc(int fd, const char *delimit, int is_expandable,
		t_binary_tree_node *node)
{
	char				*line;
	t_token				*token;
	t_expansion_build	*build;

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
		if (is_expandable == 1 && ft_strcmp(line, "\n") != 0)
		{
			token = ft_tokenize(line, 0, NULL,
					ft_create_expander_callbacks(ft_get_tokens(node)[0]->expand_var,
						NULL));
			build = token->build_expansion(token, ft_get_ht_env(node));
			ft_putendl_fd(token->last_build->token_expanded, fd);
			build->destroy(&build);
			token->destroy(&token);
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}
