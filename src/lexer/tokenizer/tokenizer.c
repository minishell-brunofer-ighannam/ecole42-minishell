/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:56:21 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/17 02:07:33 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_internal.h"
#include "tokenizer.h"

static void					*ft_destroy_tokenized_prompt(
								t_tokenized_prompt	**self_ref);
static t_tokenized_prompt	*ft_create_tokenized_prompt(
								const char *prompt,
								t_splited_prompt **splited,
								t_expander_callbacks callbacks);

t_tokenized_prompt	*ft_tokenizer(
						const char *prompt,
						t_expand_var_clbk expand_var,
						t_expand_glob_clbk expand_glob)
{
	t_splited_prompt		*splited;
	t_tokenized_prompt		*tokenized_prompt;
	t_expander_callbacks	callbacks;

	splited = ft_splitter(prompt);
	if (!splited)
		return (NULL);
	callbacks.expand_glob = expand_glob;
	callbacks.expand_var = expand_var;
	tokenized_prompt = ft_create_tokenized_prompt(prompt, &splited, callbacks);
	if (!tokenized_prompt)
		return (NULL);
	return (tokenized_prompt);
}

static t_tokenized_prompt	*ft_create_tokenized_prompt(
								const char *prompt,
								t_splited_prompt **splited,
								t_expander_callbacks callbacks)
{
	t_tokenized_prompt		*tokenized_prompt;
	t_token					**curr_token;

	tokenized_prompt = ft_calloc(1, sizeof(t_tokenized_prompt));
	if (!tokenized_prompt)
		return (NULL);
	tokenized_prompt->size = (*splited)->len;
	tokenized_prompt->original_prompt = (const char *)ft_strdup(prompt);
	tokenized_prompt->tokens = ft_calloc((*splited)->len + 1, sizeof(t_token *));
	while (--(*splited)->len >= 0)
	{
		curr_token = &tokenized_prompt->tokens[(*splited)->len];
		*curr_token = ft_tokenize((*splited)->chuncks[(*splited)->len],
				(*splited)->len, (*splited)->coords[(*splited)->len], callbacks);
		if (!*curr_token)
		{
			(*splited)->destroy(splited);
			return (ft_destroy_tokenized_prompt(&tokenized_prompt));
		}
	}
	(*splited)->destroy(splited);
	tokenized_prompt->destroy = ft_destroy_tokenized_prompt;
	return (tokenized_prompt);
}

static void	*ft_destroy_tokenized_prompt(t_tokenized_prompt	**self_ref)
{
	t_tokenized_prompt	*self;

	if (!self_ref || !*self_ref)
		return (NULL);
	self = *self_ref;
	if (self->original_prompt)
		free((char *)self->original_prompt);
	if (self->tokens)
	{
		while (--self->size >= 0)
			if (self->tokens[self->size])
				self->tokens[self->size]->destroy(&self->tokens[self->size]);
		free(self->tokens);
	}
	free(self);
	*self_ref = NULL;
	return (NULL);
}
