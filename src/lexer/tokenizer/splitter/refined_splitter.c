/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:52:01 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 22:34:55 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

static void	ft_jump_useless_quotes(char *str, int *curr_idx);
static void	ft_split_raw_token(
				char *token, int curr_idx, t_linkedlist_array *container);

char	**ft_refined_splitter(char const *str)
{
	t_linkedlist_array	*container;
	t_linkedlist_node	*curr_node;
	int					idx;
	char				**raw_split;
	char				**refined_split;

	raw_split = ft_raw_splitter(str);
	idx = 0;
	while (raw_split[idx])
		idx++;
	container = ft_new_linkedlist_array(idx);
	while (--idx >= 0)
		ft_split_raw_token(
			raw_split[idx], idx, container);
	refined_split = ft_calloc(container->nodes_amount + 1, sizeof(char *));
	idx = container->nodes_amount - 1;
	while (--container->size >= 0)
	{
		curr_node = container->list[container->size]->last;
		while (curr_node)
		{
			refined_split[idx--] = ft_strdup(curr_node->content);
			curr_node = curr_node->prev;
		}
	}
	container->destroy(&container, free);
	ft_destroy_char_matrix(&raw_split);
	return (refined_split);
}

static void	ft_split_raw_token(
				char *token, int curr_idx, t_linkedlist_array *container)
{
	char	*new_token;
	int		new_token_idx;
	int		idx;
	int		found_quote;
	int		token_len;

	token_len = ft_strlen(token);
	new_token = ft_calloc(token_len + 1, sizeof(char));
	new_token_idx = 0;
	found_quote = 0;
	idx = -1;
	while (token[++idx])
	{
		if (ft_is_quote(token, idx, NULL))
		{
			if (idx > 0 && !found_quote)
			{
				found_quote = token[idx];
				ft_jump_useless_quotes(token + idx, &idx);
			}
			else if (!found_quote)
				found_quote = token[idx];
			else if (found_quote == token[idx])
				found_quote = 0;
			if (token[idx] && token[idx + 1] && !token[idx - 1]
				&& ft_is_quote(token, idx, NULL) && !ft_is_quote(token, idx + 1, NULL))
				new_token[new_token_idx++] = token[idx];
			else if (token[idx] && !token[idx + 1] && token[idx - 1]
				&& ft_is_quote(token, idx, NULL) && !ft_is_quote(token, idx - 1, NULL))
				new_token[new_token_idx++] = token[idx];
			else if (token[idx] && token[idx + 1] && token[idx - 1]
				&& ft_is_quote(token, idx, NULL) && !ft_is_quote(token, idx + 1, NULL)
				&& ft_is_quote(token, idx, NULL) && !ft_is_quote(token, idx - 1, NULL))
				new_token[new_token_idx++] = token[idx];
		}
		else
		{
			if (!found_quote && is_reserved_token(token, idx))
			{
				if (new_token_idx > 0)
					container->push(container, curr_idx,
						ft_strdup(new_token));
				new_token_idx = 0;
				ft_bzero(new_token, token_len * sizeof(char));
				container->push(container, curr_idx,
					ft_substr(token, idx, is_reserved_token(token, idx)));
				idx += is_reserved_token(token, idx);
			}
			if (token[idx])
				new_token[new_token_idx++] = token[idx];
			else
				break ;
		}
	}
	if (new_token_idx > 0)
		container->push(container, curr_idx, ft_strdup(new_token));
	free(new_token);
}

static void	ft_jump_useless_quotes(char *str, int *curr_idx)
{
	int	idx;

	idx = 0;
	while (str[idx] && ft_is_quote(str, idx, NULL))
		idx++;
	*curr_idx += idx - 1;
}
