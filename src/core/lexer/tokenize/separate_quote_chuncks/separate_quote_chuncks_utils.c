/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_quote_chuncks_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:33:26 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:34:03 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "separate_quote_chuncks_internal.h"

static char				*ft_to_noquotes_string(
							t_token_separated_sections *self);
static void				ft_copy_to_noquote_string(
							t_token_section	**matrix,
							int len, char *string, int *string_idx);
static t_token_section	**ft_copy_matrix(t_token_separated_sections *self);
static void				*ft_destroy_token_separated_sections(
							t_token_separated_sections **self_ref);

/**
 * # ft_create_token_separated_sections
 *
 * Creates the main container for tokenized sections.
 *
 * Logic:
 * - Allocates lists for sections and coordinates.
 * - Sets utility pointers (copy_array,
 *   to_noquotes_string, destroy).
 * - Initializes auxiliary fields to NULL.
 */
t_token_separated_sections	*ft_create_token_separated_sections(void)
{
	t_token_separated_sections	*exp_sections;

	exp_sections = ft_calloc(1, sizeof(t_token_separated_sections));
	if (!exp_sections)
		return (NULL);
	exp_sections->list = ft_new_linkedlist();
	if (!exp_sections->list)
		return (ft_destroy_token_separated_sections(&exp_sections));
	exp_sections->coord_list = ft_new_linkedlist();
	if (!exp_sections->coord_list)
		return (ft_destroy_token_separated_sections(&exp_sections));
	exp_sections->copy_coord_array = ft_copy_coord_matrix;
	exp_sections->copy_array = ft_copy_matrix;
	exp_sections->to_noquotes_string = ft_to_noquotes_string;
	exp_sections->destroy = ft_destroy_token_separated_sections;
	return (exp_sections);
}

/**
 * # ft_copy_matrix
 *
 * Duplicates an array of `t_token_section**`.
 *
 * Logic:
 * - Counts the array size.
 * - Allocates a new array.
 * - Duplicates each section individually.
 */
static t_token_section	**ft_copy_matrix(t_token_separated_sections *self)
{
	int				len;
	t_token_section	**matrix;
	t_token_section	**new_matrix;

	if (self || !self->array || !*self->array)
		return (NULL);
	matrix = self->array;
	len = 0;
	while (matrix[len])
		len++;
	new_matrix = ft_calloc(len + 1, sizeof(t_token_section *));
	while (--len >= 0)
		new_matrix[len] = ft_create_token_session(
				matrix[len]->section,
				matrix[len]->quote_type
				);
	return (new_matrix);
}

/**
 * # ft_destroy_token_separated_sections
 *
 * Completely destroys the container of sections.
 *
 * Logic:
 * - Frees arrays of sections and coordinates.
 * - Frees internal lists.
 * - Frees the main structure.
 * - Sets the caller pointer to NULL.
 */
static void	*ft_destroy_token_separated_sections(
				t_token_separated_sections **self_ref)
{
	t_token_separated_sections	*self;
	int							i;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	i = -1;
	if (self->array)
	{
		while (self->array[++i])
			self->array[i]->destroy(&self->array[i]);
		free(self->array);
	}
	if (self->coord_array)
		ft_destroy_char_matrix((char ***)((void *)&self->coord_array));
	if (self->list)
		self->list->destroy(&self->list, ft_token_session_destroy_callback);
	if (self->coord_list)
		self->coord_list->destroy(&self->coord_list, free);
	free(self);
	*self_ref = NULL;
	return (NULL);
}

/**
 * # ft_to_noquotes_string
 *
 * Reconstructs the original string removing
 * external quotes of each section, without
 * altering internal content.
 *
 * Logic:
 * - Calculates final size.
 * - Copies each section ignoring
 *   delimiter quotes.
 * - Keeps internal content untouched.
 */
static char	*ft_to_noquotes_string(t_token_separated_sections *self)
{
	t_token_section	**matrix;
	char			*string;
	int				len;
	int				string_idx;

	if (!self || !self->array || !*self->array)
		return (NULL);
	matrix = self->array;
	len = self->list->size;
	string_idx = 0;
	while (--len >= 0)
		string_idx += ft_strlen(matrix[len]->section);
	string = ft_calloc(string_idx + 1, sizeof(char));
	string_idx = 0;
	len = -1;
	while (++len < self->list->size)
		ft_copy_to_noquote_string(matrix, len, string, &string_idx);
	return (string);
}

/**
 * # ft_copy_to_noquote_string
 *
 * Helper function for reconstruction without quotes.
 *
 * Logic:
 * - Copies the section character by character.
 * - Removes only quotes that delimit the entire
 *   section.
 */
static void	ft_copy_to_noquote_string(
				t_token_section	**matrix,
				int len, char *string, int *string_idx)
{
	int				section_idx;

	section_idx = -1;
	while (matrix[len]->section[++section_idx])
	{
		if (!section_idx
			&& ft_is_special_char(matrix[len]->section, section_idx, "'\""))
			section_idx++;
		string[(*string_idx)++] = matrix[len]->section[section_idx];
		if (!matrix[len]->section[section_idx + 1]
			&& ft_is_special_char(matrix[len]->section, section_idx, "'\""))
			string[--(*string_idx)] = 0;
	}
}
