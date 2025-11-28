/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:07:25 by valero            #+#    #+#             */
/*   Updated: 2025/11/27 14:15:37 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	//rl_catch_signals = 0;
	while (1)
	{
		ft_handle_sig_parent();
		line = readline(PROMPT);
		if (!line)
		{
			free(line);
			//tem que limpar tudo aqui
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		printf("line: %s\n", line);
		add_history(line);
		free(line);
	}
}
