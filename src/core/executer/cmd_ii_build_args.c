/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ii_build_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:02:15 by valero            #+#    #+#             */
/*   Updated: 2025/12/11 10:05:46 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static char	**ft_matrix_dup(char **src);

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
			ft_free_argv(node);
			return ((void)ft_destroy_char_matrix(&args));
		}
		ft_set_argv(node, i, arg);
	}
	ft_destroy_char_matrix(&args);
}

void	ft_push_glob_expanded(t_token *token, t_linkedlist *list)
{
	t_splited_prompt	*splitted;

	splitted = ft_raw_splitter(token->last_build->token_expanded);
	list->push(list, ft_matrix_dup(splitted->chuncks));
	splitted->destroy(&splitted);
}

static char	**ft_matrix_dup(char **src)
{
	char	**matrix;
	int		len;

	len = 0;
	while (src[len])
		len++;
	matrix = ft_calloc(len + 1, sizeof(char *));
	if (!matrix)
		return (NULL);
	len = -1;
	while (src[++len])
	{
		matrix[len] = ft_strdup(src[len]);
		if (!matrix[len])
			return (ft_destroy_char_matrix(&matrix));
	}
	return (matrix);
}
