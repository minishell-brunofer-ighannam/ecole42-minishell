/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ht_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:02:13 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/11 18:04:45 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	argc = 2;
	argv = NULL;
	t_linkedlist_array *ht_env;

	ht_env = ft_init_ht_env(envp);
	ft_export(ht_env, NULL);
	ft_export(ht_env, "TEST8");
	ft_export(ht_env, NULL);
	ft_env(ht_env);
	return (0);
}
