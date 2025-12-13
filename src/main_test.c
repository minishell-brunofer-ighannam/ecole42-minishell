/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:33:39 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/13 19:06:35 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "core/executer/executer.h"

int	main(int argc, char **argv, char **envp)
{
	int		status;
	void	*exec;
	char	*line;
	int		fd;

	if (argc == 1)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	ft_set_sig(0);
	ft_init_sig_parent();
	exec = ft_built_exec(envp);
	line = get_next_line(fd);
	while (line)
	{
		status = 0;
		ft_putstr_fd("\n\n", 1);
		ft_putendl_fd(line, 1);
		status = ft_executer(line, &exec);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	ft_destroy_exec(&exec);
	return (status);
}
