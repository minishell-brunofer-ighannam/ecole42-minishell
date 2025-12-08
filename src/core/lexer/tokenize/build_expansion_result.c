/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion_result.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:17:19 by valero            #+#    #+#             */
/*   Updated: 2025/12/08 15:33:09 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

static t_expansion_build	*ft_create_expansion_build(void);
static t_expansion_build	*ft_remove_quotes(
								t_expandable_object *object,
								t_expansion_build *expansion_build,
								char *glob_input,
								const char *original_token);

/**
 * # ft_build_expansion_result
 *
 * Monta o t_expansion_build final.
 *
 * Lógica:
 * - Chama ft_remove_quotes() que aplica regras de remoção
 *   de aspas do shell.
 * - Usa glob_input ou valores expandidos.
 */
t_expansion_build	*ft_build_expansion_result(t_token *token, char *glob_input)
{
	t_expansion_build	*expansion_build;
	t_expandable_object	*object;

	expansion_build = ft_create_expansion_build();
	if (!expansion_build)
		return (NULL);
	object = token->expandable_object;
	return (
		ft_remove_quotes(
			object,
			expansion_build,
			glob_input,
			token->value)
	);
}

/**
 * # ft_remove_quotes
 *
 * Remove aspas externas e ajusta resultado final.
 *
 * Lógica:
 * - Se houve erro no glob (padrões não encontrados):
 *   - Usa ft_separate_quote_chuncks() para capturar string sem aspas
 *     e salvar em glob_error.
 * - Caso contrário:
 *   - Usa expanded_glob_value se existir.
 *   - Senão expanded_value.
 *   - Senão original_token.
 * - Gera versão sem aspas via to_noquotes_string().
 */
static t_expansion_build	*ft_remove_quotes(
								t_expandable_object *object,
								t_expansion_build *expansion_build,
								char *glob_input,
								const char *original_token)
{
	t_token_separated_sections	*sep_sections;
	const char					*return_token;

	sep_sections = NULL;
	if (object && object->has_globs && !object->expanded_glob_value)
	{
		sep_sections = ft_separate_quote_chuncks(glob_input);
		expansion_build->glob_error = sep_sections->to_noquotes_string(
				sep_sections);
		sep_sections->destroy(&sep_sections);
		return (expansion_build);
	}
	if (object && object->expanded_glob_value)
		return_token = object->expanded_glob_value;
	else if (object && object->expanded_value)
		return_token = object->expanded_value;
	else
		return_token = original_token;
	sep_sections = ft_separate_quote_chuncks(return_token);
	expansion_build->token_expanded = sep_sections->to_noquotes_string(
			sep_sections);
	sep_sections->destroy(&sep_sections);
	return (expansion_build);
}

/**
 * # ft_expansion_build_dup
 *
 * Duplica um t_expansion_build.
 *
 * Lógica:
 * - Se havia erro → copia apenas glob_error.
 * - Caso contrário → copia token_expanded.
 */
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

/**
 * # ft_destroy_expansion_build
 *
 * Libera glob_error, token_expanded e a struct.
 */
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

/**
 * # ft_create_expansion_build
 *
 * Constrói struct vazia com destroy definido.
 */
static t_expansion_build	*ft_create_expansion_build(void)
{
	t_expansion_build	*expansion_build;

	expansion_build = ft_calloc(1, sizeof(t_expansion_build));
	if (!expansion_build)
		return (NULL);
	expansion_build->destroy = ft_destroy_expansion_build;
	return (expansion_build);
}
