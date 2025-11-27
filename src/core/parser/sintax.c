/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:51:10 by valero            #+#    #+#             */
/*   Updated: 2025/11/27 15:14:44 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static void	ft_jump_to_paren_closing(t_token **tokens, int *idx);

int	ft_get_precedence(t_token *token)
{
	int	max_precedence;

	max_precedence = 4;
	if (token->type == TOKEN_PAREN_OPEN)
		return (max_precedence - 0);
	if (ft_is_redirect_node(token))
		return (max_precedence - 1);
	if (token->type == TOKEN_PIPE)
		return (max_precedence - 2);
	if (token->type == TOKEN_AND || token->type == TOKEN_OR)
		return (max_precedence - 3);
	return (0);
}

int	ft_find_lower_precedence(t_token **tokens)
{
	int	idx;
	int	lower_precedence_idx;
	int	lower_precedence;
	int	curr_precedence;

	lower_precedence_idx = -1;
	lower_precedence = 4;
	idx = -1;
	while (tokens[++idx])
	{
		if (tokens[idx]->type == TOKEN_PAREN_OPEN)
			ft_jump_to_paren_closing(tokens, &idx);
		if (!tokens[idx])
			break ;
		curr_precedence = ft_get_precedence(tokens[idx]);
		if (curr_precedence && curr_precedence <= lower_precedence)
		{
			lower_precedence = curr_precedence;
			lower_precedence_idx = idx;
		}
	}
	return (lower_precedence_idx);
}

static void	ft_jump_to_paren_closing(t_token **tokens, int *idx)
{
	int	opened_parens;

	opened_parens = 0;
	if (tokens[(*idx)]->type == TOKEN_PAREN_OPEN)
		opened_parens++;
	while (tokens[++(*idx)] && opened_parens)
	{
		if (tokens[*idx]->type == TOKEN_PAREN_OPEN)
			opened_parens++;
		if (tokens[*idx]->type == TOKEN_PAREN_CLOSE)
			opened_parens--;
	}
}

bool	ft_is_redirect_node(t_token *token)
{
	if (token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_HERE_DOC_IN
		|| token->type == TOKEN_APPEND_OUT)
		return (true);
	return (false);
}
