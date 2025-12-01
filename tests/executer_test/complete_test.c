/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:39:45 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/01 17:43:30 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/core/executer/builtins/builtins.h"
#include "../../src/core/executer/env/env.h"
#include "../../src/core/lexer/lexer.h"
#include "../../src/core/parser/parser_internal.h"
#include "../tests.h"
#include "../../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_exec *exec;
	exec = ft_built_exec(envp);
	char *line;
	t_lexer *lexer;
	t_ast	*ast;

	while (1)
	{
		ft_handle_sig_parent();
		line = readline(PROMPT);
		if (!line)
		{
			free(line);
			//tem que limpar tudo aqui
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		add_history(line);
		lexer = ft_lexer(line, ft_expand_var, ft_expand_glob);
		ast = ft_ast_build(lexer, exec);
		ft_execute_tree(ast->tree->root);
		free(line);
	}
}