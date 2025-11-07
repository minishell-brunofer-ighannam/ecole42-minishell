/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:18:47 by valero            #+#    #+#             */
/*   Updated: 2025/11/06 17:26:53 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	ft_granular_split(
				char **first_split, int len, t_linkedlist	**granular_split);

char	**ft_token_split(char *line)
{
	char			**first_split;
	t_linkedlist	**granular_split;
	int				first_split_len;

	first_split = ft_split(line, ' ');
	first_split_len = 0;
	while (first_split[first_split_len])
		first_split_len++;
	granular_split = ft_calloc(first_split_len, sizeof(t_linkedlist *));
	ft_granular_split(first_split, first_split_len, granular_split);
	free(line);
}

static void	ft_granular_split(
		char **first_split, int len, t_linkedlist	**granular_split)
{
	int		i;
	char	word;

	i = -1;
	while (++i < len)
	{
		granular_split[i] = ft_new_linkedlist();
		word = first_split[i];
	}
}
