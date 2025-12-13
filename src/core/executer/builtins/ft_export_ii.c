/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_ii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:16:12 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/13 15:51:21 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_export(t_linkedlist_array *ht_env, t_token **tokens)
{
	int	i;
	int	status_temp;
	int	status;

	if (!tokens)
		return (ft_export_include(ht_env, NULL));
	i = 1;
	status = 0;
	status_temp = 0;
	while (tokens[i])
	{
		status_temp = ft_export_include(ht_env,
				tokens[i]->last_build->token_expanded);
		if (status_temp != 0)
			status = status_temp;
		i++;
	}
	return (status);
}

void	ft_free_content_ht(t_ht *content)
{
	free(content->key);
	free(((t_env_value *)(content->value))->value);
	free(content->value);
	free(content);
}
