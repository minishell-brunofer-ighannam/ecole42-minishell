/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ii_get_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:09:04 by valero            #+#    #+#             */
/*   Updated: 2025/12/11 14:07:52 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static char	**ft_matrixify(char *str);
static int	ft_get_matrix_len(t_linkedlist *list);
static char	**ft_merge_matrix(t_linkedlist *list);

char	**ft_get_args(t_token **tokens)
{
	char				**args;
	int					i;
	t_linkedlist		*list;

	list = ft_new_linkedlist();
	i = -1;
	while (tokens[++i])
	{
		if (!tokens[i]->expandable_object)
			list->push(list, ft_matrixify((char *)tokens[i]->value));
		else if (!tokens[i]->expandable_object->has_globs
			&& *tokens[i]->last_build->token_expanded)
			list->push(list,
				ft_matrixify(tokens[i]->last_build->token_expanded));
		else if (tokens[i]->last_build->token_expanded
			&& *tokens[i]->last_build->token_expanded)
			ft_push_glob_expanded(tokens[i], list);
		else if (tokens[i]->last_build->glob_error
			&& *tokens[i]->last_build->glob_error)
			list->push(list, ft_matrixify(tokens[i]->last_build->glob_error));
	}
	args = ft_merge_matrix(list);
	list->destroy(&list, ft_destroy_matrix);
	return (args);
}

static char	**ft_matrixify(char *str)
{
	char	**matrix;

	matrix = ft_calloc(2, sizeof(char *));
	if (!matrix)
		return (NULL);
	matrix[0] = ft_strdup(str);
	if (!matrix[0])
		return (ft_destroy_char_matrix(&matrix));
	return (matrix);
}

static char	**ft_merge_matrix(t_linkedlist *list)
{
	char				**matrix;
	int					matrix_i;
	int					len;
	t_linkedlist_node	*node;
	char				**content;

	len = ft_get_matrix_len(list);
	matrix = ft_calloc(len + 1, sizeof(char *));
	if (!matrix)
		return (NULL);
	matrix_i = 0;
	node = list->first;
	while (node)
	{
		content = node->content;
		len = -1;
		while (content[++len])
		{
			matrix[matrix_i++] = ft_strdup(content[len]);
			if (!matrix[matrix_i - 1])
				return (ft_destroy_char_matrix(&matrix));
		}
		node = node->next;
	}
	return (matrix);
}

static int	ft_get_matrix_len(t_linkedlist *list)
{
	int					len;
	int					idx;
	t_linkedlist_node	*node;
	char				**content;

	len = 0;
	node = list->first;
	while (node)
	{
		content = node->content;
		idx = -1;
		while (content[++idx])
			len++;
		node = node->next;
	}
	return (len);
}
