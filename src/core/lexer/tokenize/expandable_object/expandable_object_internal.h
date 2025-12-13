/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable_object_internal.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:05:35 by valero            #+#    #+#             */
/*   Updated: 2025/12/13 13:55:38 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDABLE_OBJECT_INTERNAL_H
# define EXPANDABLE_OBJECT_INTERNAL_H

# include "libft.h"
# include "../../../../data_structures/data_structures.h"
# include "../../../../utils/utils.h"
# include "../../lexer_internal.h"
# include "../separate_quote_chuncks/separate_quote_chuncks.h"
# include "expandable_object.h"

/**
 * # t_expandable_section
 *
 * Intermediate structure used to collect
 * token sections that may contain
 * expansions (`$VAR`, `$1`, `$?`, etc.).
 *
 * Stores:
 * - `list`: linked list of text sections.
 * - `coord_list`: same sections, storing
 *   {start, end}.
 * - `array` / `coord_array`: linear
 *   versions of the lists.
 *
 * Purpose:
 * Serves as a "discovery buffer." Anything
 * that can be expanded passes through here
 * before being filtered and assembled
 * into the final object.
 */
typedef struct s_expandable_section			t_expandable_section;
struct s_expandable_section
{
	const char		*src;
	t_linkedlist	*list;
	t_linkedlist	*coord_list;
	char			**array;
	int				**coord_array;
	char			**(*copy_array)(t_expandable_section *self);
	int				**(*copy_coord_array)(void *arg);
	void			*(*destroy)(t_expandable_section **self_ref);
};
t_expandable_section		*ft_create_expandable_sections(const char *str);
int							**ft_copy_coord_matrix(void *arg);
t_expandable_section		*ft_find_expandable(const char *str);
t_expandable_section		*ft_find_keys_to_expand(
								t_expandable_section *expandable_sections,
								const char *src, int *coord_in_src);
void						ft_push_expandable_key(
								t_expandable_section *expandable_sections,
								int idx, t_expandable_section *exp_keys,
								int *section_idx);

#endif
