/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:38:57 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/02 19:27:24 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "tokenize_internal.h"

static t_token_type	ft_get_token_type(const char *token);
static char			*ft_token_remove_quotes(t_token *self);
static void			*ft_destroy_token(t_token **self_ref);

/**
 * # ft_create_token
 *
 * Construtor completo de t_token.
 *
 * Lógica:
 * - Aloca a struct.
 * - Duplica string e coordenadas.
 * - Atribui callbacks.
 * - Classifica via ft_get_token_type().
 * - Se TOKEN_UNKNOWN → cria expandable_object
 *   pois pode conter $VAR ou padrões glob.
 * - Define destroy().
 */
t_token	*ft_create_token(const char *value, int position, int *coord_in_src,
		t_expander_callbacks callbacks)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->expand_var = callbacks.expand_var;
	token->expand_glob = callbacks.expand_glob;
	token->value = (const char *)ft_strdup(value);
	token->position = position;
	if (coord_in_src)
		token->coord_in_src = ft_coord_dup(coord_in_src);
	token->expand_var = callbacks.expand_var;
	token->expand_glob = callbacks.expand_glob;
	token->build_expansion = ft_build_expansion;
	token->remove_quotes = ft_token_remove_quotes;
	token->type = ft_get_token_type(token->value);
	if (token->type == TOKEN_UNKNOWN)
	{
		token->expandable_object = ft_create_expandable_object(token);
		if (!token->expandable_object)
			return (ft_destroy_token(&token));
	}
	token->destroy = ft_destroy_token;
	return (token);
}

static char	*ft_token_remove_quotes(t_token *self)
{
	t_token_separated_sections	*sep_sections;
	char						*result;

	sep_sections = ft_separate_quote_chuncks(self->value);
	result = sep_sections->to_noquotes_string(sep_sections);
	sep_sections->destroy(&sep_sections);
	return (result);
}

/**
 * # ft_get_token_type
 *
 * Classifica o token segundo operadores do shell.
 *
 * Lógica:
 * - Se tem 1 char e pertence aos símbolos conhecidos → retorna char.
 * - Se tem 2 chars e combinações conhecidas → retorna (c1<<8 | c2).
 * - Caso contrário → TOKEN_UNKNOWN.
 */
static t_token_type	ft_get_token_type(const char *token)
{
	int	len;

	len = ft_strlen(token);
	if (len == 1 && ft_strchr("|()<>;&", token[0])) // | ( ) < > ; &
		return (token[0]);
	else if (len == 2 &&
				((token[0] == '>' && ft_strchr("|&>", token[1]))   // >| >& >>
				|| (token[0] == '&' && ft_strchr("&>", token[1])) // && &>
				|| (token[0] == '<' && ft_strchr("<>", token[1])) // << <>
				|| (token[0] == '|' && token[1] == '|')           // ||
				|| (token[0] == '2' && token[1] == '>')))         // 2>
		return (token[0] << 8 | token[1]);
	else
		return (TOKEN_UNKNOWN);
}

/**
 * # ft_destroy_token
 *
 * Libera memória do token e seus subcomponentes.
 * Libera:
 * - value
 * - expandable_object e seus campos
 * - coord_in_src
 * - last_build
 * Depois zera ponteiro.
 */
static void	*ft_destroy_token(t_token **self_ref)
{
	t_token	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	if (self->value)
		free((char *)self->value);
	if (self->expandable_object)
		self->expandable_object->destroy(&self->expandable_object);
	if (self->coord_in_src)
		free(self->coord_in_src);
	if (self->last_build)
		self->last_build->destroy(&self->last_build);
	free(self);
	*self_ref = NULL;
	return (NULL);
}
