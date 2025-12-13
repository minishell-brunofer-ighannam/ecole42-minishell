/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:05:15 by valero            #+#    #+#             */
/*   Updated: 2025/12/13 13:06:38 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenize.h"
#include "expandable_object.h"
#include "expandable_object_internal.h"

static bool					ft_has_globs(
								t_expandable_section *expandable_sections);
static void					*ft_destroy_expandable_object(
								t_expandable_object **self_ref);
static	t_expandable_object	*ft_create_expansion_data(
								t_expandable_object **object,
								t_token *token, const char *src);

/**
 * # ft_create_expandable_object
 *
 * Main constructor for the expandable object.
 *
 * Logic:
 * - Allocates and initializes
 *   `t_expandable_object`.
 * - Calls `ft_create_expansion_data` to detect
 *   expansions.
 * - Copies `original_value` from the token.
 * - Sets the `destroy` callback.
 *
 * Key function: initializes everything that
 * will be used for expansion.
 */
t_expandable_object	*ft_create_expandable_object(
						t_token *token, const char *src)
{
	t_expandable_object	*object;

	object = ft_calloc(1, sizeof(t_expandable_object));
	if (!object)
		return (NULL);
	if (!ft_create_expansion_data(&object, token, src))
		return (NULL);
	object->original_value = (const char *)ft_strdup(token->value);
	if (!object->original_value)
		return (ft_destroy_expandable_object(&object));
	object->expanded_value = NULL;
	object->expanded_glob_value = NULL;
	object->expanded_chuncks = NULL;
	object->destroy = ft_destroy_expandable_object;
	return (object);
}

/**
 * # ft_copy_expansion_into_object
 *
 * Copies only selected keys from
 * `t_expandable_section` into
 * `t_expandable_object`.
 *
 * Logic:
 * - Counts the number of keys.
 * - Copies coordinates with
 *   `copy_coord_array`.
 * - Copies keys with `copy_array`.
 *
 * This is the step where discovered
 * expansions become concrete data in
 * the final object.
 */
static bool	ft_copy_expansion_into_object(
				t_expandable_object **object,
				t_expandable_section *keys_to_expand)
{
	int	keys_amount;

	keys_amount = 0;
	while (keys_to_expand->array[keys_amount])
		keys_amount++;
	if (keys_amount)
	{
		(*object)->expandable_coord_keys = keys_to_expand->copy_coord_array(
				keys_to_expand);
		if (!(*object)->expandable_coord_keys)
			return (!!ft_destroy_expandable_object(object));
		(*object)->expandable_keys = keys_to_expand->copy_array(keys_to_expand);
		if (!(*object)->expandable_keys)
			return (!!ft_destroy_expandable_object(object));
	}
	return (true);
}

/**
 * # ft_create_expansion_data
 *
 * Core of expansion discovery.
 *
 * Logic:
 * - Splits sections respecting quotes
 *   using `ft_find_expandable`.
 * - Checks for globs via `ft_has_globs`.
 * - Extracts only truly expandable keys
 *   with `ft_find_keys_to_expand`.
 * - Copies this data into the final object.
 *
 * Main "scanner" of the module.
 */
static	t_expandable_object	*ft_create_expansion_data(
								t_expandable_object **object,
								t_token *token, const char *src)
{
	t_expandable_section	*expandable_sections;
	t_expandable_section	*keys_to_expand;

	expandable_sections = ft_find_expandable(token->value);
	if (!expandable_sections)
		return (ft_destroy_expandable_object(object));
	(*object)->has_globs = ft_has_globs(expandable_sections);
	keys_to_expand = ft_find_keys_to_expand(expandable_sections,
			src, token->coord_in_src);
	if (!keys_to_expand)
		return (ft_destroy_expandable_object(object));
	if (!ft_copy_expansion_into_object(object, keys_to_expand))
	{
		keys_to_expand->destroy(&keys_to_expand);
		return (NULL);
	}
	keys_to_expand->destroy(&keys_to_expand);
	return (*object);
}

/**
 * # ft_destroy_expandable_object
 *
 * Completely destroys a
 * `t_expandable_object`.
 *
 * Logic:
 * - Frees `original_value`, `expanded_value`,
 *   and `glob_value`.
 * - Frees coordinate and key arrays.
 * - Frees `expanded_chunks`.
 *
 * Focused on avoiding leaks, as the structure
 * has multiple levels.
 */
static void	*ft_destroy_expandable_object(t_expandable_object **self_ref)
{
	t_expandable_object	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	if (self->original_value)
		free((char *)self->original_value);
	if (self->expanded_value)
		free(self->expanded_value);
	if (self->expanded_glob_value)
		free(self->expanded_glob_value);
	if (self->expandable_coord_keys)
		ft_destroy_char_matrix((char ***)&self->expandable_coord_keys);
	if (self->expandable_keys)
		ft_destroy_char_matrix(&self->expandable_keys);
	if (self->expanded_chuncks)
		ft_destroy_char_matrix(&self->expanded_chuncks);
	free(self);
	*self_ref = NULL;
	return (NULL);
}

/**
 * # ft_has_globs
 *
 * Checks if any section contains `*` *outside
 * of double quotes*.
 *
 * Important because:
 * - Glob is only applied to non-quoted content.
 *
 * Returns `true` if a valid glob exists,
 * `false` otherwise.
 */
static bool	ft_has_globs(t_expandable_section *expandable_sections)
{
	char	**array;
	int		idx;

	array = expandable_sections->array;
	idx = -1;
	while (array[++idx])
	{
		if (array[idx][0] != '"')
			if (ft_strchr(array[idx], '*'))
				return (true);
	}
	return (false);
}
