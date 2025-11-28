/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:57:56 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/27 16:29:41 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static int	ft_wait(pid_t pid_left, pid_t pid_right, int fd[2]);

int	ft_execute_pipe(t_node *node)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		fd[2];

	pipe(fd);
	pid_left = fork();
	if (pid_left == 0)
	{
		ft_handle_sig_child();
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exit(ft_execute_node(node->left));
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		ft_handle_sig_child();
		close(fd[1]);
		if (node->right->type != NODE_HERE_DOC_IN
			&& node->right->type != NODE_REDIRECT_IN)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exit(ft_execute_node(node->right));
	}
	return (ft_wait(pid_left, pid_right, fd));
}

static int	ft_wait(pid_t pid_left, pid_t pid_right, int fd[2])
{
	int	status_left;
	int	status_right;

	close(fd[0]);
	close(fd[1]);
	if (waitpid(pid_left, &status_left, 0) == -1 || waitpid(pid_right,
			&status_right, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status_right) != 0 && WEXITSTATUS(status_right) != 0)
		return (WEXITSTATUS(status_right));
	return (0);
}
