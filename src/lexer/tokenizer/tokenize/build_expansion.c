/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:09:42 by valero            #+#    #+#             */
/*   Updated: 2025/11/14 22:05:18 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

static void	ft_build_chuncks(t_token *token);
static int	ft_create_expanded_value(t_token *token);
static void	merge_expansion(t_token *token);

char	*ft_build_expansion(t_token *token)
{
	if (token->last_build)
		return (ft_strdup(token->last_build));
	if (!token->expandable_object)
		return (ft_strdup(token->value));
	ft_build_chuncks(token);
	merge_expansion(token);
	token->last_build = ft_strdup(token->expandable_object->expanded_value);
	return (ft_strdup(token->expandable_object->expanded_value));
}

static void	ft_build_chuncks(t_token *token)
{
	char				**keys;
	int					len_keys;
	t_expandable_object	*object;

	object = token->expandable_object;
	keys = object->expandable_keys;
	len_keys = 0;
	while (keys[len_keys])
		len_keys++;
	object = token->expandable_object;
	object->expanded_chuncks = ft_calloc(len_keys + 1, sizeof(char *));
	len_keys = -1;
	while (keys[++len_keys])
		object->expanded_chuncks[len_keys] = token->expand_var(keys[len_keys]);
}

static int	ft_create_expanded_value(t_token *token)
{
	int					idx;
	int					value_len;
	int					**coords;
	char				**chuncks;
	t_expandable_object	*object;

	object = token->expandable_object;
	value_len = ft_strlen(token->value);
	coords = object->expandable_coord_keys;
	idx = -1;
	while (coords[++idx])
		value_len -= coords[idx][1] - coords[idx][0] + 1;
	chuncks = object->expanded_chuncks;
	idx = -1;
	while (chuncks[++idx])
		value_len += ft_strlen(chuncks[idx]);
	object->expanded_value = ft_calloc(value_len + 1, sizeof(char));
	return (value_len);
}

static void	merge_expansion(t_token *token)
{
	int					idx;
	int					value_len;
	t_expandable_object	*object;
	int					**coords;
	int					original_i;
	int					expanded_i;
	int					len_added;
	int					chunck_i;

	object = token->expandable_object;
	coords = object->expandable_coord_keys;
	value_len = ft_create_expanded_value(token);
	len_added = 0;
	expanded_i = 0;
	idx = 0;
	original_i = -1;
	while (coords[idx] && expanded_i < value_len && object->original_value[++original_i] && expanded_i < coords[idx][1] + len_added)
	{
		if (original_i < coords[idx][0])
		{
			object->expanded_value[expanded_i++] = object->original_value[original_i];
		}
		else
		{
			chunck_i = -1;
			while (object->expanded_chuncks[idx][++chunck_i])
				object->expanded_value[expanded_i++] = object->expanded_chuncks[idx][chunck_i];
			len_added += chunck_i;
			original_i = coords[idx][1];
			idx++;
		}
	}
}
