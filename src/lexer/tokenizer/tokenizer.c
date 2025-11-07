/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:56:21 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/06 13:27:55 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/**
 *
 * @param line - is a freeable string
 */
t_token_group	*ft_tokenizer(char *line)
{
	char			**words;
	int				len_words;
	t_token_group	*token_group;

	words = ft_split(line, ' ');
	len_words = 0;
	while (words[len_words])
		len_words++;
	token_group = ft_calloc(1, sizeof(t_token_group));
	token_group->size = len_words;
	while (--len_words >= 0)
		token_group->tokens[len_words] = ft_token(words, len_words);
	return (token_group);
}

t_token	*ft_token(char **words, int idx)
{
	t_token	*token;
	int		len_word;

	len_word = ft_strlen(words);
	ft_update_token_metadata(token, words, idx);
	ft_update_token_type(token, words, idx);
}
