/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:41:19 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/08 17:04:05 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_echo(t_binary_tree_node *node)
{
	t_token	**token;
	int		i;

	token = ft_get_tokens(node);
	i = 1;
	if (token[i] && ft_strcmp("-n", token[i]->last_build->token_expanded) == 0)
		i++;
	while (token[i])
	{
		ft_putstr_fd(token[i]->last_build->token_expanded, STDOUT_FILENO);
		if (token[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!token[1] || ft_strcmp("-n", token[1]->last_build->token_expanded) != 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
