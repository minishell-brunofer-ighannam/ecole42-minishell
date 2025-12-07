/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sketch_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:35:07 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/07 17:55:25 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/reader/reader.h"

void	ft_fake_executer(const char *line, void *exec);
void	*ft_fake_create_exec(char **envp);

int	main(int argc, char **argv, char **envp)
{

	(void)argc;
	(void)argv;
	ft_reader(ft_fake_executer, ft_fake_create_exec, envp);
}

void	ft_fake_executer(const char *line, void *exec)
{
	(void)line;
	(void)exec;
}

void	*ft_fake_create_exec(char **envp)
{
	(void)envp;
	return (NULL);
}
