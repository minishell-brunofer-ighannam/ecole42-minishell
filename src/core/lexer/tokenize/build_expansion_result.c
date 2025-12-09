/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion_result.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:17:19 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:38:24 by brunofer         ###   ########.fr       */
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
 * Builds the final t_expansion_build.
 *
 * Logic:
 * - Calls ft_remove_quotes() to apply shell quote
 *   removal rules.
 * - Uses glob_input or expanded values.
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
 * Removes external quotes and adjusts the final result.
 *
 * Logic:
 * - If there was a glob error (pattern not found):
 *   - Uses ft_separate_quote_chuncks() to capture the
 *     unquoted string and save it in glob_error.
 * - Otherwise:
 *   - Uses expanded_glob_value if available.
 *   - Else uses expanded_value.
 *   - Else uses original_token.
 * - Generates a no-quotes version via to_noquotes_string().
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
 * Duplicates a t_expansion_build.
 *
 * Logic:
 * - If there was an error → copies only glob_error.
 * - Otherwise → copies token_expanded.
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
 * Frees glob_error, token_expanded, and the struct.
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
 * Constructs an empty struct with destroy defined.
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
