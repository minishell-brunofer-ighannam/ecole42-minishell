/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_keys_to_expand_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:54:33 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/13 14:03:48 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandable_object_internal.h"

static bool	ft_is_key_char(char key_char, bool is_first);
static bool	ft_is_special_key_char(char key_char);
static void	ft_track_keys(
				int *section_idx, char *token_section,
				int *coords, t_expandable_section *exp_keys);

void	ft_push_expandable_key(
			t_expandable_section *expandable_sections, int idx,
			t_expandable_section *exp_keys, int *section_idx)
{
	int			*new_coord;
	char		*token_section;
	int			*coords;

	token_section = expandable_sections->array[idx];
	coords = expandable_sections->coord_array[idx];
	if (ft_is_special_key_char(token_section[(*section_idx) + 1]))
	{
		exp_keys->list->push(exp_keys->list,
			ft_substr(token_section, (*section_idx), 2));
		new_coord = ft_new_coord(
				coords[0] + (*section_idx), coords[0] + (*section_idx) + 1);
		exp_keys->coord_list->push(exp_keys->coord_list, new_coord);
		(*section_idx)++;
	}
	else if (ft_is_key_char(token_section[(*section_idx) + 1], true))
		ft_track_keys(&(*section_idx), token_section, coords, exp_keys);
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
