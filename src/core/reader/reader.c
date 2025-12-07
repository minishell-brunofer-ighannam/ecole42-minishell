/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:57:07 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/07 18:01:00 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_internal.h"

void	ft_reader(
			void (*executer)(const char *line, void *exec),
			void *(*create_exec)(char **envp), char **envp)
{
	char	*line;
	char	*prompt;
	void	*exec;

	exec = create_exec(envp);
	prompt = ft_get_prompt();
	while (1)
	{
		// ft_handle_sig_parent();
		line = readline(prompt);
		if (!line)
			break ;
		add_history(line);
		executer(line, exec);
		free(line);
	}
	free(prompt);
}
