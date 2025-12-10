/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:34:16 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/10 10:27:08 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_binary_tree_node *node)
{
	char		*pwd;
	t_ht		*ht;

	if (ft_find_ht(ft_get_ht_env(node), "PWD"))
	{
		ht = ft_find_ht(ft_get_ht_env(node), "PWD")->content;
		pwd = ((t_env_value *)ht->value)->value;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			perror("pwd");
			return (1);
		}
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	printf("%s\n", pwd);
	return (0);
}
