/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion_result.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:17:19 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 17:29:20 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"
#include "tokenize.h"

static t_expansion_build	*ft_create_expansion_build(void);

t_expansion_build	*ft_build_expansion_result(t_token *token, char *glob_input)
{
	t_expansion_build	*expansion_build;
	t_expandable_object	*object;

	expansion_build = ft_create_expansion_build();
	if (!expansion_build)
		return (NULL);
	object = token->expandable_object;
	if (object && object->has_globs && !object->expanded_glob_value)
	{
		expansion_build->glob_error = ft_strdup(glob_input);
		return (expansion_build);
	}
	if (object && object->expanded_glob_value)
		expansion_build->token_expanded = ft_strdup(
				object->expanded_glob_value);
	else if (object && object->expanded_value)
		expansion_build->token_expanded = ft_strdup(object->expanded_value);
	else
		expansion_build->token_expanded = ft_strdup(token->value);
	return (expansion_build);
}

t_expansion_build	*ft_expansion_build_dup(t_expansion_build *last_build)
{
	t_expansion_build	*expansion_build;

	expansion_build = ft_create_expansion_build();
	if (!expansion_build)
		return (NULL);
	if (last_build->glob_error)
	{
		expansion_build->glob_error = ft_strdup(last_build->glob_error);
		return (expansion_build);
	}
	expansion_build->token_expanded = ft_strdup(last_build->token_expanded);
	return (expansion_build);
}

static void	*ft_destroy_expansion_build(t_expansion_build **self_ref)
{
	t_expansion_build	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	free(self->glob_error);
	free(self->token_expanded);
	free(self);
	*self_ref = NULL;
	return (NULL);
}

static t_expansion_build	*ft_create_expansion_build(void)
{
	t_expansion_build	*expansion_build;

	expansion_build = ft_calloc(1, sizeof(t_expansion_build));
	if (!expansion_build)
		return (NULL);
	expansion_build->destroy = ft_destroy_expansion_build;
	return (expansion_build);
}
