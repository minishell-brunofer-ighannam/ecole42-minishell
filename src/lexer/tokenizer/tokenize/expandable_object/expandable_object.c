/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:05:15 by valero            #+#    #+#             */
/*   Updated: 2025/11/14 18:50:22 by valero           ###   ########.fr       */
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
								t_token *token);

t_expandable_object	*ft_create_expandable_object(t_token *token)
{
	t_expandable_object	*object;

	object = ft_calloc(1, sizeof(t_expandable_object));
	if (!object)
		return (NULL);
	if (!ft_create_expansion_data(&object, token))
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

static	t_expandable_object	*ft_create_expansion_data(
								t_expandable_object **object,
								t_token *token)
{
	t_expandable_section	*expandable_sections;
	t_expandable_section	*keys_to_expand;

	expandable_sections = ft_find_expandable(token->value);
	if (!expandable_sections)
		return (ft_destroy_expandable_object(object));
	(*object)->has_globs = ft_has_globs(expandable_sections);
	keys_to_expand = ft_find_keys_to_expand(expandable_sections);
	if (!keys_to_expand)
		return (ft_destroy_expandable_object(object));
	(*object)->expandable_coord_keys = keys_to_expand->copy_coord_array(
			keys_to_expand);
	if (!(*object)->expandable_coord_keys)
		return (ft_destroy_expandable_object(object));
	(*object)->expandable_keys = keys_to_expand->copy_array(keys_to_expand);
	if (!(*object)->expandable_keys)
		return (ft_destroy_expandable_object(object));
	keys_to_expand->destroy(&keys_to_expand);
	return (*object);
}

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
