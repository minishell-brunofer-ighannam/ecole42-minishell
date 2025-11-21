/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:04:15 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/21 15:35:43 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_execute_cmd(t_node *node)
{
	int ret;
	pid_t pid;

	ret = 0;
	ft_built_args(node); //expande e monta o args para o comando
	if (ft_execute_redirect(node) == 1) //executa os redirects
		return (1);
	if (ft_is_builtin(node->token[0]->value) == 1)
		ret = ft_execute_builtin(node);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			execve(ft_find_path(node->ht_env, node->argv[0]), node->argv, node->envp);
		}
		waitpid(pid, NULL, 0);
	}
	return (ret);
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