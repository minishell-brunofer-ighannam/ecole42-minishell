/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_quote_chunck_session.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:31:47 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:32:11 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "separate_quote_chuncks_internal.h"

static void	*ft_destroy_token_session(t_token_section **self_ref);

/**
 * # ft_create_token_session
 *
 * Creates a `t_token_section` from a substring.
 *
 * Logic:
 * - Duplicates the substring.
 * - Sets the quote type.
 * - Assigns the destroy callback.
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
 * Duplicates an existing `t_token_section`.
 *
 * Logic:
 * - Copies the section and quote type.
 * - Keeps the same destroy callback.
 * - Used for converting lists → arrays.
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
 * Callback to destroy a `t_token_section`
 * when freeing generic lists.
 *
 * Logic:
 * - Forwards the call to the internal
 *   destroy method.
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
 * Safely destroys a `t_token_section`.
 *
 * Logic:
 * - Frees the substring.
 * - Frees the structure.
 * - Sets the caller pointer to NULL.
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
