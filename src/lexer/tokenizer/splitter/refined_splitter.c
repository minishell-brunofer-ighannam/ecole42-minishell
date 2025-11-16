/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:52:01 by valero            #+#    #+#             */
/*   Updated: 2025/11/16 17:28:40 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

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
 * ---
 *
 * Splits a command line string into refined tokens,
 * handling quotes and reserved tokens.
 *
 * Works as the second stage of lexical processing.
 * Generates an array of cleaned tokens ready for
 * parsing or execution.
 *
 * ## Logic
 * - Calls `ft_raw_splitter()` to obtain raw tokens.
 * - Allocates a linked list array to store refined tokens.
 * - Calls `refine_tokens()` to process each raw token.
 * - Converts the linked list array into a string matrix.
 * - Frees intermediate data and returns refined tokens.
 *
 * ## Parameters
 * - `str`: Raw input string to process.
 *
 * ## Returns
 * - Array of strings (`char **`) with refined tokens,
 *   NULL-terminated.
 * - Returns `NULL` if allocation fails or `str` is NULL.
 *
 * ## Notes
 * - Handles quote merging and token separation.
 * - Reserved tokens (like `>`, `|`, `&&`) are split
 *   into separate elements.
 * - Escaped spaces and quotes are preserved.
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
 * ---
 *
 * Processes each raw token from `raw_split` and stores
 * the refined version in `refined_tokens`.
 *
 * ## Logic
 * - Iterates all raw tokens.
 * - Calls `ft_refine_raw_token()` on each token.
 *
 * ## Parameters
 * - `refined_tokens`: Linked list array to store output.
 * - `raw_split`: Array of raw tokens from first split.
 * - `len_raw_split`: Number of raw tokens.
 *
 * ## Returns
 * - None (output stored in `refined_tokens`).
 *
 * ## Notes
 * - Maintains original token order.
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
 * ---
 *
 * Converts a linked list array of refined tokens into
 * a standard NULL-terminated string array.
 *
 * ## Logic
 * - Iterates nodes in reverse to preserve order.
 * - Copies each node's content using `ft_strdup()`.
 *
 * ## Parameters
 * - `refined_tokens`: Linked list array of tokens.
 * - `matrix`: Preallocated array to store copied strings.
 *
 * ## Returns
 * - None (tokens copied to `matrix`).
 *
 * ## Notes
 * - Caller must free the matrix after use.
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
	splited_prompt->chuncks = ft_calloc(splited_prompt->len + 1, sizeof(char *));
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

void	free_chunck(void *ptr)
{
	t_chunck	*chunck;

	chunck = (t_chunck *)ptr;
	chunck->destroy(&chunck);
}
