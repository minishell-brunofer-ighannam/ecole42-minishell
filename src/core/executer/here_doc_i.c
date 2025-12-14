/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:49:25 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/14 19:57:52 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static int	ft_process_heredoc(t_linkedlist_node *item_list, char *file);
static int	ft_read_line_heredoc(int fd, char *delimit, int is_expandable,
				t_binary_tree_node *node);
static int	ft_ctrl_c_d_heredoc(int fd, char *file, char *delimit, char id);
void		ft_tokenize_build_heredoc(t_binary_tree_node *node, char *line,
				int fd);
void		ft_tokenize_build_heredoc_alternative(t_binary_tree_node *node,
				char *line, int fd);

int	ft_execute_heredocs(t_binary_tree_node *node)
{
	t_linkedlist		*heredoc;
	t_linkedlist_node	*item_list;
	t_exec				*exec;

	ft_init_sig_heredoc();
	heredoc = ft_find_all_heredoc(node);
	exec = *(t_exec **)((t_ast_node *)(node->content))->exec;
	exec->heredoc = heredoc;
	exec->heredoc_files = ft_new_linkedlist();
	item_list = heredoc->last;
	while (item_list)
	{
		if (ft_process_heredoc(item_list, NULL) != 0)
		{
			ft_set_sig(0);
			return (130);
		}
		item_list = item_list->prev;
	}
	return (0);
}

static int	ft_process_heredoc(t_linkedlist_node *item_list, char *file)
{
	t_binary_tree_node	*node;
	char				*delimit;
	int					fd;
	int					is_expandable;
	t_exec				*exec;

	file = ft_generate_temp_file();
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	node = (t_binary_tree_node *)item_list->content;
	delimit = ft_get_tokens(node)[1]->remove_quotes(ft_get_tokens(node)[1]);
	if (ft_strcmp(delimit, ft_get_tokens(node)[1]->value) == 0)
		is_expandable = 1;
	else
		is_expandable = 0;
	if (ft_read_line_heredoc(fd, delimit, is_expandable, node) != 0)
		return (ft_ctrl_c_d_heredoc(fd, file, delimit, 'c'));
	close(fd);
	free(delimit);
	exec = *(t_exec **)(((t_ast_node *)(node->content))->exec);
	exec->heredoc_files->push(exec->heredoc_files, file);
	return (0);
}

static int	ft_ctrl_c_d_heredoc(int fd, char *file, char *delimit, char id)
{
	if (id == 'c')
	{
		close(fd);
		unlink(file);
		free(file);
		free(delimit);
		return (130);
	}
	else if (id == 'd')
	{
		ft_putstr_fd("minishell: warning: here-document ", 1);
		ft_putstr_fd("delimited by end-of-file (wanted `", 1);
		ft_putstr_fd(delimit, 1);
		ft_putstr_fd("')\n", 1);
		return (0);
	}
	return (0);
}

static int	ft_read_line_heredoc(int fd, char *delimit, int is_expandable,
		t_binary_tree_node *node)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_get_sig() == SIGINT)
		{
			free(line);
			ft_set_sig(0);
			return (130);
		}
		if (!line)
			return (ft_ctrl_c_d_heredoc(fd, NULL, delimit, 'd'));
		if (ft_strcmp(line, delimit) == 0)
		{
			free(line);
			break ;
		}
		if (is_expandable == 1 && ft_strcmp(line, "\n") != 0)
			ft_tokenize_build_heredoc_alternative(node, line, fd);
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

void	ft_tokenize_build_heredoc(t_binary_tree_node *node, char *line, int fd)
{
	t_token				*token;
	t_expansion_build	*build;
	int					coords[2];

	coords[0] = 0;
	coords[1] = ft_strlen(line) - 1;
	token = ft_tokenize(line, 0, (int *)coords,
			ft_create_expander_callbacks(ft_get_tokens(node)[0]->expand_var,
				NULL));
	build = token->build_expansion(token, ft_get_ht_env(node));
	if (token->expandable_object)
	{
		if (token->last_build->token_expanded)
			ft_putendl_fd(token->last_build->token_expanded, fd);
		else
			ft_putendl_fd(token->last_build->glob_error, fd);
	}
	else
		ft_putendl_fd((char *)token->value, fd);
	build->destroy(&build);
	token->destroy(&token);
}
