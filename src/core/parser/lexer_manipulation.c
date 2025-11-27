/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:19:26 by valero            #+#    #+#             */
/*   Updated: 2025/11/26 22:03:25 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static t_lexer_subset	*ft_subset_fom_subset(t_lexer_subset *self,
							int start, int end);
static void				*ft_destroy_lexer_subset(t_lexer_subset **self_ref);

t_lexer_subset	*ft_create_lexer_subset(t_lexer *lexer, int start, int end)
{
	t_lexer_subset	*subset;
	int				idx;

	if (end < start)
		return (NULL);
	subset = ft_calloc(1, sizeof(t_lexer_subset));
	if (!subset)
		return (NULL);
	subset->size = end - start + 1;
	subset->tokens = ft_calloc(subset->size + 1, sizeof(t_token *));
	if (!subset->tokens)
		return (ft_destroy_lexer_subset(&subset));
	idx = 0;
	while (start <= end)
		subset->tokens[idx++] = lexer->tokens[start++];
	subset->subset = ft_subset_fom_subset;
	subset->destroy = ft_destroy_lexer_subset;
	return (subset);
}

static t_lexer_subset	*ft_subset_fom_subset(
							t_lexer_subset *self,
							int start, int end)
{
	t_lexer_subset	*subset;
	int				idx;

	if (end < start)
		return (NULL);
	subset = ft_calloc(1, sizeof(t_lexer_subset));
	if (!subset)
		return (NULL);
	subset->size = end - start + 1;
	subset->tokens = ft_calloc(subset->size + 1, sizeof(t_token *));
	idx = 0;
	while (start <= end)
		subset->tokens[idx++] = self->tokens[start++];
	subset->subset = ft_subset_fom_subset;
	subset->destroy = ft_destroy_lexer_subset;
	return (subset);
}

static void	*ft_destroy_lexer_subset(t_lexer_subset **self_ref)
{
	t_lexer_subset	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	if (self->tokens)
		free(self->tokens);
	free(self);
	*self_ref = NULL;
	return (NULL);
}
