/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:59:37 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/28 16:35:34 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"

/**
 * # ft_tokenize
 *
 * Cria e retorna um token a partir de uma substring.
 * Encapsula ft_create_token().
 *
 * Lógica:
 * - Aloca token.
 * - Copia valor, posição e coordenadas.
 * - Define callbacks.
 * - Classifica tipo.
 */
t_token	*ft_tokenize(
			const char *chunck,
			int idx,
			int *coord_in_src,
			t_expander_callbacks callbacks)
{
	t_token	*token;

	token = ft_create_token(chunck, idx, coord_in_src, callbacks);
	if (!token)
		return (NULL);
	return (token);
}

t_expander_callbacks	ft_create_expander_callbacks(
							t_expand_var_clbk	expand_var,
							t_expand_glob_clbk	expand_glob)
{
	t_expander_callbacks	callbacks;

	callbacks.expand_var = expand_var;
	callbacks.expand_glob = expand_glob;
	return (callbacks);
}
