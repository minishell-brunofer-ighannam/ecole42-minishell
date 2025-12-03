/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:34:16 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/03 09:26:25 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_binary_tree_node *node)
{
	char	*pwd;

	pwd = ((t_env_value *)((t_ht *)((t_linkedlist_node *)ft_find_ht(ft_get_ht_env(node), "PWD"))->content)->value)->value;
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	//free(pwd);
	return (0);
}
