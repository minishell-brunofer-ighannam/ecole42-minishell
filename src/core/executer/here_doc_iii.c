/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_iii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 19:54:23 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/14 19:54:49 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	ft_tokenize_build_heredoc_alternative(t_binary_tree_node *node,
		char *line, int fd)
{
	t_token						*token;
	t_expansion_build			*build;
	t_token_separated_sections	*chunks;
	int							i;

	i = 0;
	chunks = ft_separate_quote_chuncks(line);
	while (chunks->array[i])
	{
		token = ft_create_token_hd(chunks, i, node, -1);
		build = token->build_expansion(token, ft_get_ht_env(node));
		ft_putstr_heredoc(token, chunks, fd, i);
		build->destroy(&build);
		token->destroy(&token);
		i++;
	}
	ft_putstr_fd("\n", fd);
	chunks->destroy(&chunks);
}

t_token	*ft_create_token_hd(t_token_separated_sections *chunks, int i,
		t_binary_tree_node *node, int j)
{
	char	*str_no_quotes;
	int		coords[2];
	t_token	*token;

	str_no_quotes = ft_calloc(ft_strlen(chunks->array[i]->section) + 1,
			sizeof(char));
	if (!chunks->array[i]->quote_type || chunks->array[i]->quote_type != '\'')
	{
		while (chunks->array[i]->section[++j])
			str_no_quotes[j] = chunks->array[i]->section[j];
	}
	else
	{
		while (chunks->array[i]->section[++j]
			&& j < ((int)(ft_strlen(chunks->array[i]->section) - 2)))
			str_no_quotes[j] = chunks->array[i]->section[j + 1];
	}
	coords[0] = 0;
	coords[1] = ft_strlen(str_no_quotes) - 1;
	token = ft_tokenize(str_no_quotes, 0, (int *)coords,
			ft_create_expander_callbacks(ft_get_tokens(node)[0]->expand_var,
				NULL));
	free(str_no_quotes);
	return (token);
}

void	ft_putstr_heredoc(t_token *token, t_token_separated_sections *chunks,
		int fd, int i)
{
	if (token->expandable_object)
	{
		if (token->last_build->token_expanded)
			ft_put_str_token_expanded(chunks, i, fd, token);
		else
		{
			if (!chunks->array[i]->quote_type)
				ft_putstr_fd(token->last_build->glob_error, fd);
			else
			{
				ft_putchar_fd(chunks->array[i]->quote_type, fd);
				ft_putstr_fd(token->last_build->glob_error, fd);
				ft_putchar_fd(chunks->array[i]->quote_type, fd);
			}
		}
	}
	else
		ft_putstr_fd((char *)token->value, fd);
}

void	ft_put_str_token_expanded(t_token_separated_sections *chunks, int i,
		int fd, t_token *token)
{
	if (!chunks->array[i]->quote_type)
		ft_putstr_fd(token->last_build->token_expanded, fd);
	else
	{
		ft_putchar_fd(chunks->array[i]->quote_type, fd);
		ft_putstr_fd(token->last_build->token_expanded, fd);
		ft_putchar_fd(chunks->array[i]->quote_type, fd);
	}
}
