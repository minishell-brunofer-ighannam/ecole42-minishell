/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:41:19 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/26 14:47:52 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void ft_echo(t_node *node)
{
	t_token **token;
	int i;

	token = node->token;
	i = 1;
	if (token[i] && ft_strcmp("-n", token[i]->last_build->token_expanded) == 0)
		i++;
	while (token[i])
	{
		printf("%s", token[i]->last_build->token_expanded);
		if (token[i + 1])
			printf(" ");
		i++;
	}
	if (!token[1] || ft_strcmp("-n", token[1]->last_build->token_expanded) != 0)
		printf("\n");
}
