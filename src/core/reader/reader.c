/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:57:07 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/08 15:36:09 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_internal.h"

int	ft_reader(int (*executer)(const char *line, void *exec),
		void *(*create_exec)(char **envp),
		void (*destroy_exec)(void *exec), char **envp)
{
	char	*line;
	char	*prompt;
	void	*exec;
	int		status;

	status = 0;
	exec = create_exec(envp);
	while (1)
	{
		prompt = ft_get_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		add_history(line);
		status = executer(line, &exec);
		free(line);
	}
	destroy_exec(&exec);
	return (status);
}
