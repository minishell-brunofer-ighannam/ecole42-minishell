/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expandable_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:14:58 by valero            #+#    #+#             */
/*   Updated: 2025/11/14 01:30:48 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

static void	*ft_destroy_expandable_sections(
				t_expandable_section **self_ref);

t_expandable_section	*ft_create_expandable_sections(void)
{
	t_expandable_section	*exp_sections;

	exp_sections = ft_calloc(1, sizeof(t_expandable_section));
	exp_sections->list = ft_new_linkedlist();
	exp_sections->coord_list = ft_new_linkedlist();
	exp_sections->destroy = ft_destroy_expandable_sections;
	return (exp_sections);
}

static void	*ft_destroy_expandable_sections(
			t_expandable_section **self_ref)
{
	t_expandable_section	*self;

	self = *self_ref;
	ft_destroy_char_matrix(&self->array);
	ft_destroy_char_matrix((char ***)((void *)&self->coord_array));
	self->list->destroy(&self->list, free);
	self->coord_list->destroy(&self->coord_list, free);
	free(self);
	*self_ref = NULL;
	return (NULL);
}

int	*ft_coord_dup(int *coord)
{
	int	*new_coord;

	new_coord = malloc(2 * sizeof(int));
	new_coord[0] = coord[0];
	new_coord[1] = coord[1];
	return (new_coord);
}

int	*ft_new_coord(int start, int end)
{
	int	*new_coord;

	new_coord = malloc(2 * sizeof(int));
	new_coord[0] = start;
	new_coord[1] = end;
	return (new_coord);
}
