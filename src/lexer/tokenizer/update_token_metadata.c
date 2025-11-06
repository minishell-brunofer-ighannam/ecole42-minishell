/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token_metadata.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:10:16 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/06 13:27:59 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	ft_update_token_metadata(t_token *token, char **words, int idx)
{
	token->position = idx;
	token->value = ft_strdup(words[idx]);
	if (words[idx][0] == '"')
		token->quote_type = QUOTE_DOUBLE;
	else if (words[idx][0] == '\'')
		token->quote_type = QUOTE_SINGLE;
	else
		token->quote_type = QUOTE_NONE;
}
