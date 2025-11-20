/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_object_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:14:58 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 13:26:41 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expandable_object.h"
#include "expandable_object_internal.h"

static char	**ft_copy_matrix(t_expandable_section *sections);
static void	*ft_destroy_expandable_sections(
				t_expandable_section **self_ref);

t_expandable_section	*ft_create_expandable_sections(void)
{
	t_expandable_section	*exp_sections;

	exp_sections = ft_calloc(1, sizeof(t_expandable_section));
	if (!exp_sections)
		return (NULL);
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
