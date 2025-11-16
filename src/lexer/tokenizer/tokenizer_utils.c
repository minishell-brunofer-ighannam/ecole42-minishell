/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:58:31 by valero            #+#    #+#             */
/*   Updated: 2025/11/16 15:29:35 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_internal.h"

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

