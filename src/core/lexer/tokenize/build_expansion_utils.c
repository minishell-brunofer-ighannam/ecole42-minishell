/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:48:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/24 13:30:33 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

/**
 * # ft_normilize_char_matrix
 *
 * Junta um char** em uma string única separada por espaço.
 *
 * Lógica:
 * - Calcula tamanho total (somatório dos tamanhos + espaços).
 * - Copia cada string da matriz para o buffer final.
 * - Insere espaço entre elas.
 * - Destroi a matriz.
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
 * Copia um passo da mesclagem:
 * - Se ainda está antes de uma coordenada → copia literal.
 * - Se não há coordenadas válidas → copia literal.
 * - A	o atingir coordenada da variável → copia o chunk expandido
 *   e avança índices para depois da variável.
 *
 * Executa a lógica unitária do merge.
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
 * Reconstrói o valor expandido.
 *
 * Lógica:
 * - Inicializa buffer final e índices.
 * - Percorre original e coordenadas das variáveis.
 * - A cada iteração delega à auxiliar qual conteúdo copiar:
 *      1. caractere literal
 *      1. ou chunk expandido
 * - Repete até consumir original e todas as expansões.
 *
 * É um merge manual entre string original e substituições.
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
