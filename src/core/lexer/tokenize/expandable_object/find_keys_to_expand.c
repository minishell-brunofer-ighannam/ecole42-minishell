/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_keys_to_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:05:14 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:30:58 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandable_object.h"
#include "expandable_object_internal.h"

static bool	ft_is_key_char(char key_char, bool is_first);
static bool	ft_is_special_key_char(char key_char);
static void	ft_extract_keys(
				char *token_section, int *coords,
				t_expandable_section *exp_keys);
static void	ft_track_keys(
				int *section_idx, char *token_section,
				int *coords, t_expandable_section *exp_keys);

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
		t_expandable_section *expandable_sections)
{
	t_expandable_section	*exp_keys;
	t_linkedlist			*list;
	t_linkedlist			*coord_list;
	int						idx;

	exp_keys = ft_create_expandable_sections();
	if (!exp_keys)
		return (expandable_sections->destroy(&expandable_sections));
	idx = -1;
	while (expandable_sections->array[++idx])
		ft_extract_keys(expandable_sections->array[idx],
			expandable_sections->coord_array[idx], exp_keys);
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
		char *token_section, int *coords,
		t_expandable_section *exp_keys)
{
	int	section_idx;
	int	*new_coord;

	section_idx = -1;
	while (token_section[++section_idx])
	{
		if (token_section[section_idx + 1]
			&& ft_is_special_char(token_section, section_idx, "$"))
		{
			if (ft_is_special_key_char(token_section[section_idx + 1]))
			{
				exp_keys->list->push(exp_keys->list,
					ft_substr(token_section, section_idx, 2));
				new_coord = ft_new_coord(
						coords[0] + section_idx, coords[0] + section_idx + 1);
				exp_keys->coord_list->push(exp_keys->coord_list, new_coord);
				section_idx++;
			}
			else if (ft_is_key_char(token_section[section_idx + 1], true))
				ft_track_keys(&section_idx, token_section, coords, exp_keys);
		}
	}
}

/**
 * # ft_track_keys
 *
 * Handles keys like `$VAR_NAME`.
 *
 * Logic:
 * - Advances character by character checking
 *   `ft_is_key_char`.
 * - Stores the complete substring.
 * - Creates coordinates relative to the
 *   original token.
 *
 * This is where the most sensitive logic
 * of variable parsing occurs.
 */
static void	ft_track_keys(
		int *section_idx, char *token_section,
		int *coords, t_expandable_section *exp_keys)
{
	int	key_idx;
	int	*new_coord;

	(*section_idx)++;
	key_idx = (*section_idx);
	while (token_section[key_idx] && ft_is_key_char(
			token_section[key_idx], (*section_idx) == key_idx))
		key_idx++;
	exp_keys->list->push(exp_keys->list,
		ft_substr(token_section,
			*section_idx - 1, key_idx - (*section_idx - 1)));
	new_coord = ft_new_coord(
			coords[0] + (*section_idx) - 1, coords[0] + key_idx - 1);
	exp_keys->coord_list->push(exp_keys->coord_list, new_coord);
	*section_idx = key_idx - 1;
}

/**
 * # ft_is_key_char
 *
 * Checks if a character is part of a
 * variable name.
 *
 * Rules:
 * - First char: letter or `_`.
 * - Remaining chars: alphanumeric or `_`.
 */
static bool	ft_is_key_char(char key_char, bool is_first)
{
	if ((is_first && (ft_isalpha(key_char) || key_char == '_'))
		|| (!is_first && (ft_isalnum(key_char) || key_char == '_')))
		return (true);
	return (false);
}

/**
 * # ft_is_special_key_char
 *
 * Verifica chaves especiais de um caractere só:
 * $, ?, #, *, @, -, dígitos, etc.
 */
static bool	ft_is_special_key_char(char key_char)
{
	if (ft_isdigit(key_char) || ft_strchr("$!?#*@-", key_char))
		return (true);
	return (false);
}
