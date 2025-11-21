/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:48:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/20 18:36:17 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

char	*ft_normilize_char_matrix(char **matrix)
{
	int		matrix_size;
	int		matix_idx;
	int		str_idx;
	char	*result;

	if (!matrix)
		return (NULL);
	matrix_size = 0;
	matix_idx = -1;
	while (matrix[++matix_idx])
		matrix_size += ft_strlen(matrix[matix_idx]);
	result = ft_calloc(matrix_size + matix_idx + 1, sizeof(char));
	matrix_size = 0;
	matix_idx = -1;
	while (matrix[++matix_idx])
	{
		str_idx = -1;
		while (matrix[matix_idx][++str_idx])
			result[matrix_size++] = matrix[matix_idx][str_idx];
		if (matrix[matix_idx + 1])
			result[matrix_size++] = ' ';
	}
	ft_destroy_char_matrix(&matrix);
	return (result);
}
