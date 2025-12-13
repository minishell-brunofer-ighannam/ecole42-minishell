/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_iii.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:01:52 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/13 12:36:46 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_status_cmd_with_null_path(t_binary_tree_node *node)
{
	if (ft_get_argv(node)[0] == NULL && ft_get_tokens(node)[0]->value[0])
		return (0);
	else
		return (127);
}
