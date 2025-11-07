/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:57:59 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/05 17:36:57 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	handle_signals();
	rl_catch_signals = 0;
	line = readline(PROMPT);
	while (line)
	{
		if (!line)
		{
			free(line);
			break ;
		}
		printf("line: %s\n", line);
		add_history(line);
		free(line);
		line = readline(PROMPT);
	}
}
