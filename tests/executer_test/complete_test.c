/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:39:45 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/02 16:49:39 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/core/executer/builtins/builtins.h"
#include "../../src/core/executer/env/env.h"
#include "../../src/core/lexer/lexer.h"
#include "../../src/core/parser/parser_internal.h"
#include "../tests.h"
#include "../../includes/minishell.h"

void	free_ast_node(void *arg)
{
	t_ast_node	*node;

	if (!arg)
		return ;
	node = (t_ast_node *)arg;
	node->destroy(&node, NULL);
}

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
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		add_history(line);
		callbacks = ft_create_expander_callbacks(ft_expand_var, ft_expand_glob);
		ast = ft_parser(line, callbacks, exec, free_ast_node);
		if (ast)
		{
			ft_execute_tree(ast->tree->root);
			ast->destroy(&ast, free_ast_node);
		}
		dup2(fd_out, STDOUT_FILENO);
		dup2(fd_in, STDIN_FILENO);
		free(line);
	}
}