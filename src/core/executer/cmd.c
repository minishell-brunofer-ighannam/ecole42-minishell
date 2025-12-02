/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:04:15 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/02 16:52:51 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_execute_cmd(t_binary_tree_node *node)
{
	int status;
	pid_t pid;

	status = 0;
	ft_built_args(node); //expande e monta o args para o comando
	if (ft_is_builtin(ft_get_tokens(node)[0]->value) == 1)
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
			status = execve(ft_find_path(ft_get_ht_env(node), ft_get_argv(node)[0]), ft_get_argv(node), ft_get_envp(node));
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
	ft_free_argv(node);
	return (0);
}


int ft_expand_tokens(t_binary_tree_node *node)
{
	t_token **token;
	int i;
	t_expansion_build *build;

	i = 0;
	token = ft_get_tokens(node);
	while (token[i])
	{
		build = token[i]->build_expansion(token[i], ft_get_ht_env(node));
		build->destroy(&build);
		i++;
	}
	return(i);
}

void ft_built_args(t_binary_tree_node *node)
{
	t_token **token;
	int i;

	ft_init_argv(node, ft_expand_tokens(node) + 1);
	i = 0;
	token = ft_get_tokens(node);
	while (token[i])
	{
		ft_set_argv(node, i, token[i]->last_build->token_expanded);
		i++;
	}
}