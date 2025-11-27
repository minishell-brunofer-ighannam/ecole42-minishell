/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:57:56 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/26 10:43:21 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

//no pipe, se um lado dá erro, o outro recebe uma entrada vazia

static int ft_wait(pid_t pid_left, pid_t pid_right);

int ft_execute_pipe(t_node *node)
{
	pid_t pid_left;
	pid_t pid_right;
	int fd[2];
	int status;

	pipe(fd);
	pid_left = fork();
	if (pid_left == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		status = ft_execute_node(node->left);
		exit(status);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(fd[1]);
		if (node->right->type != NODE_HERE_DOC_IN && node->right->type != NODE_REDIRECT_IN)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		status = ft_execute_node(node->right);
		exit(status);
	}
	close(fd[0]);
	close(fd[1]);
	status = ft_wait(pid_left, pid_right);
	return(status);
}

static int ft_wait(pid_t pid_left, pid_t pid_right)
{
	int status_left;
	int status_right;

	if (waitpid(pid_left, &status_left, 0) == -1 || waitpid(pid_right, &status_right, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status_right) != 0 && WEXITSTATUS(status_right) != 0)
		return (WEXITSTATUS(status_right));
	return (0);
}
