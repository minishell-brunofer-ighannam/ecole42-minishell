/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:07:25 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:47:43 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int	status;

	(void)argc;
	(void)argv;
	ft_set_sig(0);
	ft_init_sig_parent();
	status = ft_reader(ft_executer, (void *(*)(char **))ft_built_exec,
			ft_destroy_exec, envp);
	return (status);
}
