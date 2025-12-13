/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:59:37 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/13 12:33:33 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"

/**
 * # ft_tokenize
 *
 * Creates and returns a token from a substring.
 * Wraps ft_create_token().
 *
 * Logic:
 * - Allocates the token.
 * - Copies value, position, and coordinates.
 * - Sets callbacks.
 * - Classifies the type.
 */
t_token	*ft_tokenize(
			const char *src,
			int idx,
			int *coord_in_src,
			t_expander_callbacks callbacks)
{
	t_token	*token;

	token = ft_create_token(src, idx, coord_in_src, callbacks);
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
