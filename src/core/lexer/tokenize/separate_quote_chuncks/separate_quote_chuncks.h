/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_quote_chuncks.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:52:40 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:36:28 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATE_QUOTE_CHUNCKS_H
# define SEPARATE_QUOTE_CHUNCKS_H

# include "../../../../data_structures/data_structures.h"

/**
 * # t_token_section
 *
 * Represents an isolated token segment after splitting
 * by quotes. Stores the raw substring, the type of
 * quote that delimited it, and a destroy callback.
 *
 * Usage:
 * - Identify the nature of the segment (unquoted,
 *   double-quoted, single-quoted).
 * - Allow reconstruction and scanning without losing
 *   structural information.
 */
typedef struct s_token_section				t_token_section;
struct s_token_section
{
	char			*section;
	char			quote_type;
	void			*(*destroy)(t_token_section **self_ref);
};

/**
 * # t_token_separated_sections
 *
 * Main container storing all separated sections.
 * Maintains lists of sections and coordinates,
 * equivalent arrays, and utility callbacks.
 *
 * Logic:
 * - Collect individual segments while scanning the string.
 * - Store coordinates for precise reconstruction.
 * - Convert lists to arrays for fast access.
 * - Provide safe destruction and a function to
 *   reconstruct the string without external quotes.
 */
typedef struct s_token_separated_sections	t_token_separated_sections;
struct s_token_separated_sections
{
	t_linkedlist	*list;
	t_linkedlist	*coord_list;
	t_token_section	**array;
	int				**coord_array;
	t_token_section	**(*copy_array)(t_token_separated_sections *self);
	int				**(*copy_coord_array)(void *arg);
	char			*(*to_noquotes_string)(t_token_separated_sections *self);
	void			*(*destroy)(t_token_separated_sections **self_ref);
};

t_token_separated_sections	*ft_separate_quote_chuncks(const char *str);

#endif
