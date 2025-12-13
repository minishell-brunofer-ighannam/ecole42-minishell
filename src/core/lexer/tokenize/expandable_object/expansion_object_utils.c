/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_object_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:14:58 by valero            #+#    #+#             */
/*   Updated: 2025/12/13 13:11:05 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandable_object.h"
#include "expandable_object_internal.h"

static char	**ft_copy_matrix(t_expandable_section *sections);
static void	*ft_destroy_expandable_sections(
				t_expandable_section **self_ref);

/**
 * # ft_create_expandable_sections
 *
 * Creates an empty `t_expandable_section`.
 *
 * Logic:
 * - Allocates memory.
 * - Creates `list` and `coord_list`.
 * - Assigns callbacks:
 *   - `copy_array`
 *   - `copy_coord_array`
 *   - `destroy`
 *
 * General container for sections to be analyzed.
 */
t_expandable_section	*ft_create_expandable_sections(const char *str)
{
	t_expandable_section	*exp_sections;

	exp_sections = ft_calloc(1, sizeof(t_expandable_section));
	if (!exp_sections)
		return (NULL);
	exp_sections->src = str;
	exp_sections->list = ft_new_linkedlist();
	if (!exp_sections->list)
		return (ft_destroy_expandable_sections(&exp_sections));
	exp_sections->coord_list = ft_new_linkedlist();
	if (!exp_sections->coord_list)
		return (ft_destroy_expandable_sections(&exp_sections));
	exp_sections->copy_coord_array = ft_copy_coord_matrix;
	exp_sections->copy_array = ft_copy_matrix;
	exp_sections->destroy = ft_destroy_expandable_sections;
	return (exp_sections);
}

/**
 * # ft_destroy_expandable_sections
 *
 * Completely destroys a `t_expandable_section`.
 *
 * Logic:
 * - Frees the `array` and `coord_array`.
 * - Destroys `list` and `coord_list` along
 *   with their contents.
 */
static void	*ft_destroy_expandable_sections(
			t_expandable_section **self_ref)
{
	t_expandable_section	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	if (self->array)
		ft_destroy_char_matrix(&self->array);
	if (self->coord_array)
		ft_destroy_char_matrix((char ***)((void *)&self->coord_array));
	if (self->list)
		self->list->destroy(&self->list, free);
	if (self->coord_list)
		self->coord_list->destroy(&self->coord_list, free);
	free(self);
	*self_ref = NULL;
	return (NULL);
}

/**
 * # ft_copy_matrix
 *
 * Duplicates the string array of
 * `t_expandable_section`.
 *
 * Logic:
 * - Counts elements.
 * - Duplicates each item using `ft_strdup`.
 *
 * Used to copy results without modifying
 * the original buffer.
 */
static char	**ft_copy_matrix(t_expandable_section *sections)
{
	char		**array;
	int			array_len;
	char		**new_array;

	array = sections->array;
	array_len = 0;
	while (array[array_len])
		array_len++;
	new_array = ft_calloc(array_len + 1, sizeof(char **));
	array_len = -1;
	while (array[++array_len])
	{
		new_array[array_len] = ft_strdup(array[array_len]);
		if (!new_array[array_len])
		{
			while (--array_len >= 0)
				free(new_array[array_len]);
			free(new_array);
			return (NULL);
		}
	}
	return (new_array);
}

/**
 * # ft_copy_coord_matrix
 *
 * Duplicates the coordinate matrix.
 *
 * Logic:
 * - Iterates through each coordinate.
 * - Duplicates using `ft_coord_dup`.
 *
 * Used by the final object to store its
 * own coordinates.
 */
int	**ft_copy_coord_matrix(void *arg)
{
	int						**array;
	int						array_len;
	int						**new_array;
	t_expandable_section	*sections;

	sections = (t_expandable_section *)arg;
	array = sections->coord_array;
	array_len = 0;
	while (array[array_len])
		array_len++;
	new_array = ft_calloc(array_len + 1, sizeof(int **));
	array_len = -1;
	while (array[++array_len])
	{
		new_array[array_len] = ft_coord_dup(array[array_len]);
		if (!new_array[array_len])
		{
			while (--array_len >= 0)
				free(new_array[array_len]);
			free(new_array);
			return (NULL);
		}
	}
	return (new_array);
}
