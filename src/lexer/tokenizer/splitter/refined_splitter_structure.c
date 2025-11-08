/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_splitter_structure.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:53:38 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 13:32:21 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

static void	*ft_refined_splitter_push_token(
				t_refined_splitter	*self, int idx, char *token);
static void	*ft_refined_splitter_destroy(t_refined_splitter **self_ref);

t_refined_splitter	*ft_new_refined_splitter(int size)
{
	t_refined_splitter	*refined_splitter;

	refined_splitter = ft_calloc(1, sizeof(t_refined_splitter));
	if (!refined_splitter)
		return (NULL);
	refined_splitter->size = size;
	refined_splitter->push_token = ft_refined_splitter_push_token;
	refined_splitter->destroy = ft_refined_splitter_destroy;
	refined_splitter->token_list = ft_calloc(size + 1, sizeof(t_linkedlist));
	while (--size >= 0)
	{
		refined_splitter->token_list[size] = ft_new_linkedlist();
		if (!refined_splitter->token_list[size])
		{
			while (++size < refined_splitter->size)
				refined_splitter->token_list[size]->destroy(
					&refined_splitter->token_list[size], free);
			free(refined_splitter);
			return (NULL);
		}
	}
	return (refined_splitter);
}

static void	*ft_refined_splitter_push_token(
				t_refined_splitter	*self, int idx, char *token)
{
	t_linkedlist	*list;

	list = self->token_list[idx];
	list->push(list, token);
	self->tokens_amount++;
	return (NULL);
}

static void	*ft_refined_splitter_destroy(t_refined_splitter **self_ref)
{
	t_refined_splitter	*self;
	t_linkedlist		*list;

	self = *self_ref;
	while (--self->size >= 0)
	{
		list = self->token_list[self->size];
		list->destroy(&list, free);
	}
	free(self);
	*self_ref = NULL;
	return (NULL);
}
