/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:04:15 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/17 12:37:52 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int ft_cmd(t_node *node)
{
	int pid;

	if (node->built_in == 1)
	{
		//call built-in function
		//atualiza o ? no env com o que a built in retornar (status de saída)
	}
	else
	{
		//fork e execve
		//waitpid com &status para pegar o status de saída e atualizar o ? no env
	}
}