/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:07:25 by valero            #+#    #+#             */
/*   Updated: 2025/12/03 08:30:50 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_exec *exec;
	exec = ft_built_exec(envp);
	char *line;
	t_expander_callbacks callbacks;
	t_ast	*ast;
	int fd_out;
	int fd_in;

	fd_out = dup(STDOUT_FILENO);
	fd_in = dup(STDIN_FILENO);
	while (1)
	{
		
		ft_handle_sig_parent();
		line = readline(PROMPT);
		if (!line)
		{
			ft_destroy_exec(exec);
			close(fd_out);
			close(fd_in);
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		add_history(line);
		callbacks = ft_create_expander_callbacks(ft_expand_var, ft_expand_glob);
		ast = ft_parser(line, callbacks, exec, free_ast_node);
		if (ast)
			ft_execute_tree(ast);
		dup2(fd_out, STDOUT_FILENO);
		dup2(fd_in, STDIN_FILENO);
		free(line);
	}
}
