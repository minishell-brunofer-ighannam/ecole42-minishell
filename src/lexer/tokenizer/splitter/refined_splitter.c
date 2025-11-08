/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:52:01 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 13:28:35 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

static void	ft_jump_useless_quotes(char *str, int *curr_idx);
static void	ft_split_raw_token(
				char *token, int curr_idx, t_refined_splitter *splitter);

char	**ft_refined_splitter(char const *str)
{
	t_refined_splitter	*splitter;
	t_linkedlist_node	*curr_node;
	int					idx;
	char				**raw_split;
	char				**refined_split;

	raw_split = ft_raw_splitter(str);
	idx = 0;
	while (raw_split[idx])
		idx++;
	splitter = ft_new_refined_splitter(idx);
	while (--idx >= 0)
		ft_split_raw_token(
			raw_split[idx], idx, splitter);
	refined_split = ft_calloc(splitter->tokens_amount, sizeof(char *));
	idx = 0;
	while (--splitter->size >= 0)
	{
		curr_node = splitter->token_list[splitter->size]->last;
		while (curr_node)
		{
			refined_split[idx++] = ft_strdup(curr_node->content);
			curr_node = curr_node->prev;
		}
	}
	splitter->destroy(&splitter);
	ft_destroy_char_matrix(&raw_split);
	return (refined_split);
}

static void	ft_split_raw_token(
				char *token, int curr_idx, t_refined_splitter *splitter)
{
	char	*new_token;
	int		new_token_idx;
	int		idx;
	int		found_quote;
	int		token_len;

	token_len = ft_strlen(token);
	new_token = ft_calloc(token_len, sizeof(char));
	new_token_idx = 0;
	found_quote = 0;
	idx = -1;
	while (token[++idx])
	{
		if (ft_is_quote(token, idx))
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
			if (!ft_is_quote(token, idx))
				new_token[new_token_idx++] = token[idx];
		}
		else
		{
			if (!found_quote && is_reserved_token(token, idx))
			{
				if (new_token_idx > 0)
					splitter->push_token(splitter, curr_idx,
						ft_strdup(new_token));
				new_token_idx = 0;
				ft_bzero(new_token, token_len * sizeof(char));
				idx += is_reserved_token(token, idx);
				splitter->push_token(splitter, curr_idx,
					ft_substr(token, idx, is_reserved_token(token, idx)));
			}
			new_token[new_token_idx++] = token[idx];
		}
	}
	if (new_token_idx > 0)
		splitter->push_token(splitter, curr_idx, ft_strdup(new_token));
	free(new_token);
}

static void	ft_jump_useless_quotes(char *str, int *curr_idx)
{
	int	idx;

	idx = 0;
	while (str[idx] && ft_is_quote(str, idx))
		idx++;
	*curr_idx += idx;
}
