/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:26 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/04 18:38:47 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_cmd(t_node *cmd, char **envp)
{
	int pid;


	if (cmd->built_in == 1)
	{
		//call function
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			/* code */
		}
	}

}
