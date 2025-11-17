/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:38:47 by valero            #+#    #+#             */
/*   Updated: 2025/11/17 02:28:48 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLITTER_INTERNAL_H
# define SPLITTER_INTERNAL_H

# include "../../../data_structures/data_structures.h"
# include "../../lexer_utils/lexer_utils.h"
# include "../tokenizer_internal.h"
# include "splitter.h"
# include <stdbool.h>

/**
 * # t_quote_state
 *
 * ---
 *
 * Represents the internal progression of quote
 * parsing while scanning a command line.
 *
 * ## States
 * - `NO_QUOTE_OPEN`: No quote currently active.
 * - `QUOTE_OPEN`: A quote character was detected
 *   and is being processed.
 * - `INSIDE_QUOTE`: Text is currently within an
 *   open quote block.
 * - `CLOSED_QUOTE`: The last quote was closed and
 *   awaits reset to `NO_QUOTE_OPEN`.
 *
 * ## Notes
 * - Used as a simple state machine to manage
 *   quotation parsing.
 * - Prevents misinterpretation of separators and
 *   operators inside quotes.
 */
typedef enum e_quote_state							t_quote_state;
enum e_quote_state
{
	NO_QUOTE_OPEN,
	QUOTE_OPEN,
	INSIDE_QUOTE,
	CLOSED_QUOTE,
};

/**
 * # t_quote_info
 *
 * ---
 *
 * Bundles data required for managing quote parsing.
 *
 * ## Fields
 * - `state`: Current quote state (see `t_quote_state`).
 * - `open_quote_type`: Stores which quote type (`'`
 *   or `"`) opened the current quoted section.
 *
 * ## Notes
 * - Centralizes all quote-related tracking in a
 *   single structure.
 * - Used throughout raw splitting and lexing logic
 *   to maintain context.
 */
typedef struct s_quote_info							t_quote_info;
struct s_quote_info
{
	t_quote_state	state;
	int				open_quote_type;
};

typedef struct s_int_array							t_int_array;
struct s_int_array
{
	int	len;
	int	*array;
};

typedef struct s_refine_raw_token_params			t_refine_raw_token_vars;
struct s_refine_raw_token_params
{
	char	*new_token;
	int		idx_new_token;
	int		idx;
	int		found_quote;
	int		token_len;
};

typedef struct s_chunck								t_chunck;
struct s_chunck
{
	char	*chunck;
	int		*coord;
	void	*(*destroy)(t_chunck **self_ref);
};

t_chunck			*ft_create_chunck(
						char *token,
						int coord_start,
						int coord_end);
t_splited_prompt	*ft_create_splited_prompt(void);
bool				ft_is_quote(const char *str, int idx, char *other_symbols);
void				ft_raw_splitter_get_words_position(
						const char *str, t_int_array *array);
t_splited_prompt	*ft_raw_splitter(char const *str);
void				ft_refine_raw_token(
						t_chunck raw_token, int curr_idx,
						t_linkedlist_array *container);
t_splited_prompt	*ft_refined_splitter(char const *str);

#endif
