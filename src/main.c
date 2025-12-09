/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:07:25 by valero            #+#    #+#             */
/*   Updated: 2025/12/08 21:43:37 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_set_sig(0);
	ft_init_sig_parent();
	return (ft_reader(ft_executer, (void *(*)(char **))ft_built_exec,
			ft_destroy_exec, envp));
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_expander_callbacks	callbacks;
// 	t_ast					*ast;
// 	t_exec					*exec;
// 	char					*line;

// 	(void)argc;
// 	(void)argv;
// 	exec = ft_built_exec(envp);

// 	while (1)
// 	{
// 		ft_handle_sig_parent();
// 		line = readline(PROMPT);
// 		if (!line)
// 			break ;
// 		add_history(line);
// 		callbacks = ft_create_expander_callbacks(ft_expand_var, ft_expand_glob);
// 		ast = ft_parser(line, callbacks, &exec, free_ast_node);
// 		if (ast)
// 		{
// 			//ast->print(ast);
// 			ft_execute_tree(ast);
// 		}
// 		free(line);
// 	}
// 	ft_destroy_exec(&exec);
// 	return(0);
// }
