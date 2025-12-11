/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ii_build_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:02:15 by valero            #+#    #+#             */
/*   Updated: 2025/12/10 23:09:08 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	ft_destroy_matrix(void *arg)
{
	char	**matrix;

	matrix = arg;
	ft_destroy_char_matrix(&matrix);
}

void	ft_build_args_alternative(t_binary_tree_node *node)
{
	t_token	**tokens;
	char	**args;
	char	*arg;
	int		i;

	ft_expand_tokens(node);
	tokens = ft_get_tokens(node);
	args = ft_get_args(tokens);
	i = 0;
	while (args[i])
		i++;
	ft_init_argv(node, i + 1);
	i = -1;
	while (args[++i])
	{
		arg = ft_strdup(args[i]);
		if (!arg)
		{
			// TODO: isadora, free the exec argv
			return ((void)ft_destroy_char_matrix(&args));
		}
		ft_set_argv(node, i, ft_strdup(args[i]));
	}
	ft_destroy_char_matrix(&args);
}
