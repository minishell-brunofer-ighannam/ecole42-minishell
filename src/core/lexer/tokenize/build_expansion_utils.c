/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:48:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/09 18:39:35 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

/**
 * # ft_normilize_char_matrix
 *
 * Joins a char** into a single string separated by spaces.
 *
 * Logic:
 * - Calculates the total length (sum of string lengths + spaces).
 * - Copies each string from the matrix into the final buffer.
 * - Inserts spaces between them.
 * - Frees the matrix.
 */
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

/**
 * # ft_merge_copy_unit
 *
 * Copies a single step of the merge:
 * - If still before a coordinate → copy literally.
 * - If there are no valid coordinates → copy literally.
 * - Upon reaching a variable coordinate → copy the expanded
 *   chunk and advance indices past the variable.
 *
 * Executes the unit logic of the merge.
 */
static void	ft_merge_copy_unit(t_expandable_object *obj,
				int *idx, int *main_i, int *exp_i)
{
	int		chunck_i;
	int		**coords;
	char	**exp_chuncks;

	exp_chuncks = obj->expanded_chuncks;
	coords = obj->expandable_coord_keys;
	if (coords && coords[*idx] && *main_i < coords[*idx][0])
		obj->expanded_value[(*exp_i)++] = obj->original_value[(*main_i)++];
	else if ((!coords && obj->original_value[*main_i]))
		obj->expanded_value[(*exp_i)++] = obj->original_value[(*main_i)++];
	else if (coords && coords[*idx] && *main_i < coords[*idx][0]
		&& !coords[*idx + 1] && obj->original_value[*main_i])
		obj->expanded_value[(*exp_i)++] = obj->original_value[(*main_i)++];
	else if (coords && !coords[*idx] && obj->original_value[*main_i])
		obj->expanded_value[(*exp_i)++] = obj->original_value[(*main_i)++];
	else
	{
		chunck_i = -1;
		while (exp_chuncks[*idx][++chunck_i])
			obj->expanded_value[(*exp_i)++] = exp_chuncks[*idx][chunck_i];
		*main_i = coords[*idx][1] + 1;
		(*idx)++;
	}
}

/**
 * # ft_merge_expansion
 *
 * Reconstructs the expanded value.
 *
 * Logic:
 * - Initializes the final buffer and indices.
 * - Iterates over the original string and variable coordinates.
 * - Each iteration delegates to the helper which content to copy:
 *      1. literal character
 *      2. or expanded chunk
 * - Repeats until the original string and all expansions are consumed.
 *
 * It's a manual merge between the original string and substitutions.
 */
void	ft_merge_expansion(t_token *token)
{
	int					idx;
	t_expandable_object	*object;
	int					**coords;
	int					original_i;
	int					expanded_i;

	if (!token->expandable_object->expandable_keys)
		return ;
	object = token->expandable_object;
	coords = object->expandable_coord_keys;
	ft_create_expanded_value(token);
	expanded_i = 0;
	idx = 0;
	original_i = 0;
	while ((coords && coords[idx]) || object->original_value[original_i])
		ft_merge_copy_unit(object, &idx, &original_i, &expanded_i);
}
