/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:58:31 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 23:04:47 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
#include "../../utils/utils.h"

/**
 * # ft_coord_dup
 *
 * Duplicates a coordinate [start, end].
 *
 * Logic:
 * - Allocates a new array of 2 integers.
 * - Copies start and end from the original.
 *
 * Role:
 * Provides independent coordinates when multiple structures
 * need to reference the same string boundaries.
 */
int	*ft_coord_dup(int *coord)
{
	int	*new_coord;

	new_coord = malloc(2 * sizeof(int));
	new_coord[0] = coord[0];
	new_coord[1] = coord[1];
	return (new_coord);
}

/**
 * # ft_new_coord
 *
 * Creates a new coordinate [start, end].
 *
 * Logic:
 * - Allocates an array of 2 integers.
 * - Assigns values based on the given arguments.
 *
 * Role:
 * Simple utility to record regions of the original string,
 * used by both the splitter and the lexer.
 */
int	*ft_new_coord(int start, int end)
{
	int	*new_coord;

	new_coord = malloc(2 * sizeof(int));
	new_coord[0] = start;
	new_coord[1] = end;
	return (new_coord);
}

void	ft_print_structure_not_closed_error(const char *src, int error_idx)
{
	int		i;
	char	curr_char[2];

	curr_char[1] = 0;
	if (!src || error_idx < 0)
		return ;
	i = -1;
	while (src[++i] && i < error_idx + error_idx)
	{
		curr_char[0] = src[i];
		if (i != error_idx)
			ft_putstr_fd((char *)curr_char, 2);
		else
			ft_print_bold_read((char *)curr_char, 2);
	}
	ft_putchar_fd('\n', 2);
	i = -1;
	while (src[++i] && i < error_idx + 2)
	{
		if (i != error_idx)
			ft_putchar_fd(' ', 2);
		else
			ft_print_bold_read("^", 2);
	}
	ft_print_bold_read("syntax error: structure not closed\n", 2);
}
