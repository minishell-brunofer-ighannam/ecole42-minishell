/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:27:17 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/10 19:02:17 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_reader(void)
{
	char	*line;

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

int	verify_quotes(char *line)
{
	int	i;
	int	quotes_count;
	int	first_quote_index;
	int	quote_type;

	quotes_count = 0;
	first_quote_index = 0;
	quote_type = 0;
	i = -1;
	while (line[++i])
	{
		if (ft_is_quote(line, i, NULL))
		{
			if (!quotes_count && !line)
				quotes_count++;
			if (quotes_count && line[i] == quote_type)
			{
				quotes_count--;
				first_quote_index = 0;
			}
			if (!first_quote_index)
				first_quote_index = i;
			if (!quote_type || line[i] == quote_type)
				quote_type = quote_type;
		}
	}
	return (first_quote_index);
}
