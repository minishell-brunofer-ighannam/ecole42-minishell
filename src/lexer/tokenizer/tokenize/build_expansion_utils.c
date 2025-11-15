/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:48:52 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/15 15:42:57 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

static t_expansion_build	*ft_create_expansion_build(void);

t_expansion_build	*ft_build_expansion_result(t_token *token, char *glob_input)
{
	t_expansion_build	*expansion_build;
	t_expandable_object	*object;

	expansion_build = ft_create_expansion_build();
	if (!expansion_build)
		return (NULL);
	object = token->expandable_object;
	if (!object)
	{
		expansion_build->token_expanded = ft_strdup(object->original_value);
		return (expansion_build);
	}
	if (object->has_globs && !object->expanded_glob_value)
	{
		expansion_build->glob_error = ft_strdup(glob_input);
		return (expansion_build);
	}
	if (object->expanded_glob_value)
		expansion_build->token_expanded = ft_strdup(
				object->expanded_glob_value);
	else if (object->expanded_value)
		expansion_build->token_expanded = ft_strdup(object->expanded_value);
	else
		expansion_build->token_expanded = ft_strdup(object->original_value);
	return (expansion_build);
}

t_expansion_build	*ft_expansion_build_dup(t_expansion_build *last_build)
{
	t_expansion_build	*expansion_build;

	expansion_build = ft_create_expansion_build();
	if (!expansion_build)
		return (NULL);
	if (last_build->glob_error)
	{
		expansion_build->glob_error = ft_strdup(last_build->glob_error);
		return (expansion_build);
	}
	expansion_build->token_expanded = ft_strdup(last_build->token_expanded);
	return (expansion_build);

}

char	*ft_normilize_char_matrix(char **matrix)
{
	int		matrix_size;
	int		matix_idx;
	int		str_idx;
	char	*result;

	matrix_size = 0;
	matix_idx = -1;
	while (matrix[++matix_idx])
		matrix_size += ft_strlen(matrix[matix_idx]);
	result = ft_calloc(matrix_size + 1, sizeof(char));
	matrix_size = 0;
	matix_idx = -1;
	while (matrix[++matix_idx])
	{
		str_idx = -1;
		while (matrix[matix_idx][++str_idx])
			result[matrix_size++] = matrix[matix_idx][str_idx];
	}
	return (result);
}

static void	*ft_destroy_expansion_build(t_expansion_build **self_ref)
{
	t_expansion_build	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	free(self->glob_error);
	free(self->token_expanded);
	free(self);
	*self_ref = NULL;
	return (NULL);
}

static t_expansion_build	*ft_create_expansion_build(void)
{
	t_expansion_build	*expansion_build;

	expansion_build = ft_calloc(1, sizeof(t_expansion_build));
	if (!expansion_build)
		return (NULL);
	expansion_build->destroy = ft_destroy_expansion_build;
	return (expansion_build);
}
