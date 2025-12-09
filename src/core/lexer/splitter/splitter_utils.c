/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:57:24 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:22:46 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

/**
 * # ft_is_quote
 *
 * Checks if a character is a valid quote
 * (single, double, or listed in
 * `other_symbols`) and respects escape
 * rules via backslash.
 */
bool	ft_is_quote(const char *str, int idx, char *other_symbols)
{
	bool	is_quote;

	is_quote = (str[idx] == '\'' || str[idx] == '"');
	if (other_symbols)
		is_quote = (is_quote || ft_strchr(other_symbols, str[idx]));
	if (!idx && (is_quote))
		return (true);
	if (!ft_is_valid_backslash(str, idx - 1) && (is_quote))
		return (true);
	return (false);
}

static void	*ft_destroy_splited_prompt(t_splited_prompt **self_ref)
{
	t_splited_prompt	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	ft_destroy_char_matrix(&self->chuncks);
	ft_destroy_char_matrix((char ***)&self->coords);
	free(self);
	*self_ref = NULL;
	return (NULL);
}

t_splited_prompt	*ft_create_splited_prompt(void)
{
	t_splited_prompt	*splited_prompt;

	splited_prompt = ft_calloc(1, sizeof(t_splited_prompt));
	splited_prompt->destroy = ft_destroy_splited_prompt;
	return (splited_prompt);
}

static void	*ft_destroy_chunck(t_chunck **self_ref)
{
	t_chunck	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	free(self->chunck);
	free(self->coord);
	free(self);
	*self_ref = NULL;
	return (NULL);
}

t_chunck	*ft_create_chunck(char *token, int coord_start, int coord_end)
{
	t_chunck	*chunck;

	chunck = ft_calloc(1, sizeof(t_chunck));
	chunck->chunck = ft_strdup(token);
	chunck->coord = ft_calloc(2, sizeof(int));
	chunck->coord[0] = coord_start;
	chunck->coord[1] = coord_end;
	chunck->destroy = ft_destroy_chunck;
	return (chunck);
}
