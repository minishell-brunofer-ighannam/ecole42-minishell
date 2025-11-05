/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:28:06 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/05 20:26:37 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*generic_token_types(
					t_token *token, char **words, int idx, int len_word);
static t_token	*simulate_token(char **words, int idx, int right);

void	ft_update_token_type(t_token *token, char **words, int idx)
{
	int		len_word;
	t_token	*left_token;
	t_token	*right_token;

	len_word = ft_strlen(words[idx]);
	left_token = simulate_token(words, idx, 0);
	right_token = simulate_token(words, idx, 1);
	generic_token_types(token, words, idx, len_word);
	if (left_token && (left_token->type == TOKEN_PIPE
			|| left_token->type == TOKEN_OR || left_token->type == TOKEN_AND
			|| left_token->type == TOKEN_PAREN_OPEN))
		token->type = TOKEN_CMD;
	free(left_token);
	free(right_token);
}

static t_token	*generic_token_types(
	t_token *token, char **words, int idx, int len_word)
{
	if (token->quote_type != QUOTE_NONE)
		token->type = TOKEN_ARG;
	else if (idx == 0)
		token->type = TOKEN_CMD;
	else if (len_word == 1 && words[idx][0] == '|')
		token->type = TOKEN_PIPE;
	else if (len_word == 2 && words[idx][0] == '|' && words[idx][1] == '|')
		token->type = TOKEN_OR;
	else if (len_word == 2 && words[idx][0] == '&' && words[idx][1] == '&')
		token->type = TOKEN_AND;
	else if (len_word == 1 && words[idx][0] == '(')
		token->type = TOKEN_PAREN_OPEN;
	else if (len_word == 1 && words[idx][0] == ')')
		token->type = TOKEN_PAREN_CLOSE;
	else if (len_word == 1 && words[idx][0] == '<')
		token->type = TOKEN_REDIRECT_IN;
	else if (len_word == 1 && words[idx][0] == '>')
		token->type = TOKEN_REDIRECT_OUT;
	else if (len_word == 1 && words[idx][0] == '<<')
		token->type = TOKEN_HERE_DOC_IN;
	else if (len_word == 1 && words[idx][0] == '>>')
		token->type = TOKEN_HERE_DOC_OUT;
}

static t_token	*simulate_token(char **words, int idx, int right)
{
	int		len_word;
	t_token	*sim_token;

	len_word = ft_strlen(words[idx]);
	if (right)
	{
		if (!words[idx + 1])
			return (NULL);
		sim_token = ft_calloc(1, sizeof(t_token));
		generic_token_types(sim_token, words, idx + 1, len_word);
		return (sim_token);
	}
	if (!idx)
		return (NULL);
	sim_token = ft_calloc(1, sizeof(t_token));
	generic_token_types(sim_token, words, idx - 1, len_word);
	return (sim_token);
}
