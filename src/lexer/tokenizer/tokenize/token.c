/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:38:57 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/12 19:20:58 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

static int	**find_expandable(char *str);
static t_token_type	ft_get_token_type(char *token);

t_token	*ft_create_token(const char *value, int position,
	int coord_in_src[2], t_expander_callbacks callbacks)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->expand_var = callbacks.expand_var;
	token->expand_glob = callbacks.expand_glob;
	token->value = value;
	token->position = position;
	token->coord_in_src[0] = coord_in_src[0];
	token->coord_in_src[1] = coord_in_src[1];
	token->build_expansion = ft_build_expansion;
	token->type = ft_get_token_type(token->value);
	if (token->type == TOKEN_ARG)
		token->expandable_object;
}

char	*ft_build_expansion(t_token *self)
{
//
}

static t_token_type	ft_get_token_type(char *token)
{
	int	len;

	len = ft_strlen(token);
	if (len == 1 && ft_strchr("|()<>;&", token[0]))			// | ( ) < > ; &
		return (token[0]);
	else if (len == 2 && (
			(token[0] == '>' && ft_strchr("|&>", token[1]))	// >| >& >>
		|| (token[0] == '&' && ft_strchr("&>", token[1]))	// && &>
		|| (token[0] == '<' && ft_strchr("<>", token[1]))	// << <>
		|| (token[0] == '|' && token[1] == '|')				// ||
		|| (token[0] == '2' && token[1] == '>')))			// 2>
		return (token[0] << 8 | token[1]);
	else
		return (TOKEN_ARG);
}

static t_expandable_object	*ft_create_expandable_object(t_token *token)
{
	t_expandable_object	*object;

	object = ft_calloc(1, sizeof(t_expandable_object));
	object->original_value = token->value;
	object->expanded_value = NULL;
	object->expanded_glob_value = NULL;
	object->idx_on_token_src = find_expandable(token->value);
	object->expanded_chuncks = NULL;
}

static int	**find_expandable(char *str)
{
	int	i;
	t_linkedlist	*list;

	i = -1;
	while (str[++i])
	{
		if (ft_is_special_char(str, i, "$"))
		{
			if (is_variable_char(str[i], i == 0))

		}
	}

}

static bool	is_variable_char(char c, bool is_first)
{
	if (is_first && (ft_isalpha(c) || c == '_')
		|| (!is_first && ft_isalnum(c)) || c == '_')
		return (true);
	return (false);
}
