/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_quote_chunck_session.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:31:47 by valero            #+#    #+#             */
/*   Updated: 2025/11/23 17:17:38 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "separate_quote_chuncks_internal.h"

static void	*ft_destroy_token_session(t_token_section **self_ref);

/**
 * # ft_create_token_session
 *
 * Cria um t_token_section a partir de um trecho.
 *
 * Lógica:
 * - Duplica a substring.
 * - Define tipo de aspa.
 * - Atribui callback de destruição.
 */
t_token_section	*ft_create_token_session(char *session, char quote_type)
{
	t_token_section	*token_session;

	token_session = ft_calloc(1, sizeof(t_token_section));
	if (session)
		token_session->section = ft_strdup(session);
	token_session->quote_type = quote_type;
	token_session->destroy = ft_destroy_token_session;
	return (token_session);
}

/**
 * # ft_token_session_dup
 *
 * Duplica um t_token_section existente.
 *
 * Lógica:
 * - Copia seção e tipo de aspa.
 * - Mantém o mesmo callback destroy.
 * - Usado para conversão de listas → arrays.
 */
t_token_section	*ft_token_session_dup(t_token_section *token_session)
{
	t_token_section	*new_token_session;

	new_token_session = ft_calloc(1, sizeof(t_token_section));
	if (token_session->section)
		new_token_session->section = ft_strdup(token_session->section);
	new_token_session->quote_type = token_session->quote_type;
	new_token_session->destroy = token_session->destroy;
	return (new_token_session);
}

/**
 * # ft_token_session_destroy_callback
 *
 * Callback para destruir um t_token_section
 * ao liberar listas genéricas.
 *
 * Lógica:
 * - Encaminha para o método destroy interno.
 */
void	ft_token_session_destroy_callback(void *arg)
{
	t_token_section	*token_session;

	token_session = (t_token_section *)arg;
	token_session->destroy(&token_session);
}

/**
 * # ft_destroy_token_session
 *
 * Destrói de forma segura um t_token_section.
 *
 * Lógica:
 * - Libera substring.
 * - Libera estrutura.
 * - Zera ponteiro chamador.
 */
static void	*ft_destroy_token_session(t_token_section **self_ref)
{
	t_token_section	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	free(self->section);
	free(self);
	*self_ref = NULL;
	return (NULL);
}
