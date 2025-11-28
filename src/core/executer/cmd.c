/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:04:15 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/28 16:21:30 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_execute_cmd(t_node *node)
{
	int status;
	pid_t pid;

	status = 0;
	ft_built_args(node); //expande e monta o args para o comando
	if (ft_is_builtin(node->token[0]->value) == 1)
	{
		if (ft_execute_redirect(node) == 1) //executa os redirects. Se algum der errado, não executa o comando.
			return (1);
		status = ft_execute_builtin(node);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			ft_handle_sig_child();
			if (ft_execute_redirect(node) == 1) //executa os redirects. Se algum der errado, não executa o comando.
				return (1);
			status = execve(ft_find_path(node->ht_env, node->argv[0]), node->argv, node->envp);
			if (status == -1)
				exit (127);
			exit(0);		
		}
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}
		if (WIFEXITED(status) != 0 && WEXITSTATUS(status) != 0)
			return (WEXITSTATUS(status));
	}
	return (0);
}


int ft_expand_tokens(t_node *node)
{
	t_token **token;
	int i;

	i = 0;
	token = node->token;
	while (token[i])
	{
		token[i]->build_expansion(token[i], node->ht_env);
		i++;
	}
	return(i);
}

void ft_built_args(t_node *node)
{
	t_token **token;
	int i;

	node->argv = ft_calloc(ft_expand_tokens(node) + 1, sizeof(char *));
	i = 0;
	token = node->token;
	while (token[i])
	{
		node->argv[i] = token[i]->last_build->token_expanded;
		i++;
	}
}