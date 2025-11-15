/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_keys_to_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:05:14 by valero            #+#    #+#             */
/*   Updated: 2025/11/14 16:53:42 by valero           ###   ########.fr       */
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

static void	ft_extract_keys(
		char *token_section, int *coords,
		t_expandable_section *exp_keys)
{
	int	section_idx;
	int	*new_coord;

	section_idx = -1;
	while (token_section[++section_idx])
	{
		if (ft_is_special_char(token_section, section_idx, "$"))
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
			else
				ft_track_keys(&section_idx, token_section, coords, exp_keys);
		}
	}
}

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

static bool	ft_is_key_char(char key_char, bool is_first)
{
	if ((is_first && (ft_isalpha(key_char) || key_char == '_'))
		|| (!is_first && (ft_isalnum(key_char) || key_char == '_')))
		return (true);
	return (false);
}

static bool	ft_is_special_key_char(char key_char)
{
	if (ft_isdigit(key_char) || ft_strchr("$!?#*@-", key_char))
		return (true);
	return (false);
}
