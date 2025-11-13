/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_expandable_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:14:58 by valero            #+#    #+#             */
/*   Updated: 2025/11/13 18:15:39 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

t_expandable_section	*ft_create_expandable_sections(void)
{
	t_expandable_section	*exp_sections;

	exp_sections = ft_calloc(1, sizeof(t_expandable_section));
	exp_sections->list = ft_new_linkedlist();
	exp_sections->coord_list = ft_new_linkedlist();
	return (exp_sections);
}

int	*ft_coord_dup(int *coord)
{
	int	*new_coord;

	new_coord = malloc(2 * sizeof(int));
	new_coord[0] = coord[0];
	new_coord[1] = coord[1];
	return (new_coord);
}
