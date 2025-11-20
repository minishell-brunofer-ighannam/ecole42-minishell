/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:09:42 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 17:11:07 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

static void	ft_build_chuncks(t_token *token, t_linkedlist_array *ht_env);
static int	ft_create_expanded_value(t_token *token);
static void	ft_merge_expansion(t_token *token);
static char	*ft_expand_globs(t_token *token);

t_expansion_build	*ft_build_expansion(
						t_token *token,
						t_linkedlist_array *ht_env)
{
	t_expansion_build	*expansion_build;
	char				*glob_input;

	if (token->last_build)
		return (ft_expansion_build_dup(token->last_build));
	if (!token->expandable_object)
		return (ft_build_expansion_result(token, NULL));
	ft_build_chuncks(token, ht_env);
	ft_merge_expansion(token);
	glob_input = ft_expand_globs(token);
	expansion_build = ft_build_expansion_result(token, glob_input);
	if (!expansion_build)
		return (NULL);
	token->last_build = ft_expansion_build_dup(expansion_build);
	if (!token->last_build)
	{
		free(glob_input);
		expansion_build->destroy(&expansion_build);
		return (NULL);
	}
	free(glob_input);
	return (expansion_build);
}

static void	ft_build_chuncks(t_token *token, t_linkedlist_array *ht_env)
{
	char				**keys;
	int					len_keys;
	t_expandable_object	*object;

	if (!token->expandable_object->expandable_keys)
		return ;
	object = token->expandable_object;
	keys = object->expandable_keys;
	len_keys = 0;
	while (keys[len_keys])
		len_keys++;
	object = token->expandable_object;
	object->expanded_chuncks = ft_calloc(len_keys + 1, sizeof(char *));
	len_keys = -1;
	while (keys[++len_keys])
		object->expanded_chuncks[len_keys] = token->expand_var(
				keys[len_keys], ht_env);
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

static void	ft_merge_expansion(t_token *token)
{
	int					idx;
	t_expandable_object	*object;
	int					**coords;
	int					original_i;
	int					expanded_i;
	int					chunck_i;

	if (!token->expandable_object->expandable_keys)
		return ;
	object = token->expandable_object;
	coords = object->expandable_coord_keys;
	ft_create_expanded_value(token);
	expanded_i = 0;
	idx = 0;
	original_i = 0;
	while ((coords && coords[idx]) || object->original_value[original_i])
	{
		if (coords && coords[idx] && original_i < coords[idx][0])
			object->expanded_value[expanded_i++] = object->original_value[original_i++];
		else if ((!coords && object->original_value[original_i]))
			object->expanded_value[expanded_i++] = object->original_value[original_i++];
		else if (coords && coords[idx] && original_i < coords[idx][0] && !coords[idx + 1] && object->original_value[original_i])
			object->expanded_value[expanded_i++] = object->original_value[original_i++];
		else if (coords && !coords[idx] && object->original_value[original_i])
			object->expanded_value[expanded_i++] = object->original_value[original_i++];
		else
		{
			chunck_i = -1;
			while (object->expanded_chuncks[idx][++chunck_i])
				object->expanded_value[expanded_i++] = object->expanded_chuncks[idx][chunck_i];
			original_i = coords[idx][1] + 1;
			idx++;
		}
	}
}

static char	*ft_expand_globs(t_token *token)
{
	t_expandable_object	*object;
	char				*glob_input;

	object = token->expandable_object;
	if (object->has_globs)
	{
		if (object->expanded_value)
			object->expanded_glob_value = ft_normilize_char_matrix(
				token->expand_glob(object->expanded_value));
		else
			object->expanded_glob_value = ft_normilize_char_matrix(
					token->expand_glob(object->original_value));
	}
	if (object->expanded_value)
		glob_input = ft_strdup(object->expanded_value);
	else
		glob_input = ft_strdup(object->original_value);
	return (glob_input);
}
