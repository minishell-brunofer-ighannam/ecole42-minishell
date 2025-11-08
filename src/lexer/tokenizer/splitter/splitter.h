/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:38:47 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 13:37:27 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLITTER_H
# define SPLITTER_H

# include "../../../linkedlist/linkedlist.h"
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
typedef enum e_quote_state			t_quote_state;
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
typedef struct s_quote_info			t_quote_info;
struct s_quote_info
{
	t_quote_state	state;
	int				open_quote_type;
};

typedef struct s_int_array			t_int_array;
struct s_int_array
{
	int	len;
	int	*array;
};

typedef struct s_refined_splitter	t_refined_splitter;
struct s_refined_splitter
{
	int				size;
	int				tokens_amount;
	t_linkedlist	**token_list;
	void			*(*push_token)(
			t_refined_splitter *self, int idx, char *token);
	void			*(*destroy)(t_refined_splitter **self);
};

bool				ft_is_valid_backslash(const char *str, int idx);
bool				ft_is_quote(const char *str, int idx);
int					is_reserved_token(char *str, int idx);
void				ft_raw_splitter_get_words_position(
						const char *str, t_int_array *array);
char				**ft_raw_splitter(char const *str);
t_refined_splitter	*ft_new_refined_splitter(int size);
char				**ft_refined_splitter(char const *str);

#endif
