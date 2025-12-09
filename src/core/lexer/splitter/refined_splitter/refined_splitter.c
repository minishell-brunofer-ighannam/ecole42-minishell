/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:52:01 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:21:53 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refined_splitter_internal.h"

void		free_chunck(void *ptr);
static void	copy_to_matrix(
				t_linkedlist_array *refined_tokens,
				t_splited_prompt *splited_prompt);
static void	refine_tokens(
				t_linkedlist_array *refined_tokens,
				t_splited_prompt *raw_split);

/**
 * # ft_refined_splitter
 *
 * Complete refinement pipeline:
 * - Uses `ft_raw_splitter` to create raw tokens.
 * - Creates an array of lists to hold refined tokens.
 * - Refines each token with `refine_tokens`.
 * - Converts lists into the final matrix with
 *   `copy_to_matrix`.
 * - Frees temporary structures.
 *
 * Returns a properly cleaned and finalized
 * `t_splited_prompt`.
 */
t_splited_prompt	*ft_refined_splitter(char const *str)
{
	t_linkedlist_array	*refined_tokens;
	t_splited_prompt	*raw_split;
	t_splited_prompt	*refined_split;

	raw_split = ft_raw_splitter(str);
	refined_tokens = ft_new_linkedlist_array(raw_split->len);
	refine_tokens(refined_tokens, raw_split);
	refined_split = ft_create_splited_prompt();
	copy_to_matrix(refined_tokens, refined_split);
	refined_tokens->destroy(&refined_tokens, free_chunck);
	raw_split->destroy(&raw_split);
	return (refined_split);
}

/**
 * # refine_tokens
 *
 * Iterates over all raw tokens from the
 * raw split and calls `ft_refine_raw_token`
 * to process each one.
 *
 * Responsible only for the outer loop.
 */
static void	refine_tokens(
				t_linkedlist_array *refined_tokens,
				t_splited_prompt *raw_split)
{
	int			idx_raw_token;
	t_chunck	raw_token;

	idx_raw_token = -1;
	while (++idx_raw_token < raw_split->len)
	{
		raw_token.chunck = raw_split->chuncks[idx_raw_token];
		raw_token.coord = raw_split->coords[idx_raw_token];
		ft_refine_raw_token(raw_token, idx_raw_token, refined_tokens);
	}
}

/**
 * # copy_to_matrix
 *
 * Converte o array de listas de tokens refinados
 * em um `t_splited_prompt` linear.
 *
 * Lógica:
 * - Aloca matriz final.
 * - Varre cada lista de trás pra frente (ordem preservada).
 * - Duplica chuncks e coordenadas para a estrutura final.
 */
static void	copy_to_matrix(
				t_linkedlist_array *refined_tokens,
				t_splited_prompt *splited_prompt)
{
	t_linkedlist_node	*curr_node;
	int					node_idx;
	int					list_idx;
	t_chunck			*content;

	splited_prompt->len = refined_tokens->nodes_amount;
	splited_prompt->chuncks = ft_calloc(
			splited_prompt->len + 1, sizeof(char *));
	splited_prompt->coords = ft_calloc(splited_prompt->len + 1, sizeof(int *));
	node_idx = refined_tokens->nodes_amount - 1;
	list_idx = refined_tokens->size;
	while (--list_idx >= 0)
	{
		curr_node = refined_tokens->list[list_idx]->last;
		while (curr_node)
		{
			content = (t_chunck *)curr_node->content;
			splited_prompt->chuncks[node_idx] = ft_strdup(content->chunck);
			splited_prompt->coords[node_idx] = ft_coord_dup(content->coord);
			node_idx--;
			curr_node = curr_node->prev;
		}
	}
}

/**
 * # free_chunck
 *
 * Simple wrapper that calls the destructor
 * of `t_chunck`.
 * Needed to pass as a callback when
 * destroying lists.
 */
void	free_chunck(void *ptr)
{
	t_chunck	*chunck;

	chunck = (t_chunck *)ptr;
	chunck->destroy(&chunck);
}
