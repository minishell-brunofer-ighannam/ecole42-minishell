/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:22:09 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/02 10:58:40 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_subshell(t_binary_tree_node *node)
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		status = ft_execute_node(node->left);
		exit(status);
	}
	waitpid(pid, &status, 0);
	return(status);
}
