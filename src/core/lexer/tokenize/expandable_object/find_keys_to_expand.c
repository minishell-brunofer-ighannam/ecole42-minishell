/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_keys_to_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:05:14 by valero            #+#    #+#             */
/*   Updated: 2025/12/13 18:11:09 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandable_object_internal.h"

static int	ft_get_src_idx(char **array, int chunk_idx, int src_idx, int curr_idx);
static void	ft_extract_keys(t_expandable_section *expandable_sections,
				int idx, t_expandable_section *exp_keys, int *coord_in_src);

/**
 * # ft_find_keys_to_expand
 *
 * Filters *only* the truly expandable parts.
 *
 * Logic:
 * - Iterates over all found sections.
 * - Uses `ft_extract_keys` to extract keys
 *   ($X, ${var}, $?).
 * - Converts lists into arrays.
 * - Destroys the original structure, returning
 *   only the filtered data.
 *
 * Essential function: separates “potential
 * sections” from “actual keys”.
 */
t_expandable_section	*ft_find_keys_to_expand(
		t_expandable_section *expandable_sections,
		const char *src, int *coord_in_src)
{
	t_expandable_section	*exp_keys;
	t_linkedlist			*list;
	t_linkedlist			*coord_list;
	int						idx;

	exp_keys = ft_create_expandable_sections(src);
	if (!exp_keys)
		return (expandable_sections->destroy(&expandable_sections));
	idx = -1;
	while (expandable_sections->array[++idx])
		ft_extract_keys(expandable_sections, idx, exp_keys, coord_in_src);
	list = exp_keys->list;
	coord_list = exp_keys->coord_list;
	exp_keys->array = (char **)list->to_array(
			list, (void *(*)(void *content))ft_strdup, free);
	exp_keys->coord_array = (int **)coord_list->to_array(
			coord_list, (void *(*)(void *content))ft_coord_dup, free);
	expandable_sections->destroy(&expandable_sections);
	return (exp_keys);
}

/**
 * # ft_extract_keys
 *
 * Extracts expansion keys within a section.
 *
 * Logic:
 * - Traverses `token_section`.
 * - Detects `$`:
 *   - If the next character is special → short
 *     key (`$1`, `$?`).
 *   - Otherwise, calls `ft_track_keys` for
 *     long keys ($VAR).
 * - Creates correct coordinates relative to
 *   the original string.
 */
static void	ft_extract_keys(
		t_expandable_section *expandable_sections, int idx,
		t_expandable_section *exp_keys, int *coord_in_src)
{
	int			section_idx;
	int			*new_coord;
	char		*token_section;
	int			*coords;

	(void)coord_in_src;
	token_section = expandable_sections->array[idx];
	coords = expandable_sections->coord_array[idx];
	section_idx = -1;
	while (token_section[++section_idx])
	{
		if (token_section[section_idx + 1]
			&& ft_is_special_char(token_section, section_idx, "$"))
			ft_push_expandable_key(
				expandable_sections, idx, exp_keys, &section_idx);
		else if (ft_is_special_char(token_section, section_idx, "$")
			&& ft_is_special_char(exp_keys->src,
				ft_get_src_idx(expandable_sections->array,
					idx, coord_in_src[0], section_idx), "\"'"))
		{
			exp_keys->list->push(exp_keys->list, ft_strdup(""));
			new_coord = ft_new_coord(coords[0], coords[0]);
			exp_keys->coord_list->push(exp_keys->coord_list, new_coord);
		}
	}
}

static int	ft_get_src_idx(
				char **array, int chunk_idx,
				int src_idx, int curr_idx)
{
	int	len;

	len = 0;
	while (chunk_idx >= 0)
	{
		len += ft_strlen(array[chunk_idx]);
		chunk_idx--;
	}
	return (src_idx + len + curr_idx);
}
