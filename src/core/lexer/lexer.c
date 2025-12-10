/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:56:21 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/24 22:53:01 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
#include "lexer.h"

static void		*ft_destroy_lexer(
					t_lexer	**self_ref);
static t_lexer	*ft_create_lexer(
					const char *prompt,
					t_splited_prompt **splited,
					t_expander_callbacks callbacks);

/**
 * # ft_lexer
 *
 * High-level function. Combines splitter + lexer.
 *
 * Logic:
 * - Calls ft_splitter() to divide the raw line into chunks.
 * - Prepares expansion callbacks (variables and glob).
 * - Creates the final structure via ft_create_lexer().
 *
 * Responsibility:
 * Main entry point. Returns a fully prepared t_lexer
 * ready for the expansion phase.
 */
t_lexer	*ft_lexer(
						const char *prompt,
						t_expand_var_clbk expand_var,
						t_expand_glob_clbk expand_glob)
{
	t_splited_prompt		*splited;
	t_lexer					*lexer;
	t_expander_callbacks	callbacks;
	int						error_idx;

	if (!prompt || !*prompt)
		return (NULL);
	error_idx = ft_prompt_validator(prompt);
	if (error_idx > -1)
	{
		ft_print_structure_not_closed_error(prompt, error_idx);
		return (NULL);
	}
	splited = ft_splitter(prompt);
	if (!splited)
		return (NULL);
	callbacks = ft_create_expander_callbacks(expand_var, expand_glob);
	lexer = ft_create_lexer(prompt, &splited, callbacks);
	if (!lexer)
		return (NULL);
	return (lexer);
}

/**
 * # ft_create_lexer
 *
 * Constructs a t_lexer from the splitter result.
 *
 * Logic:
 * - Allocates the main structure.
 * - Copies the original prompt (for debugging and reconstruction).
 * - Creates the token array with the exact size.
 * - Iterates over the splitter chunks in reverse order:
 *       - For each chunk, creates a token via ft_tokenize().
 *       - Passes coordinates and expansion callbacks.
 * - On error: safely destroys all allocated memory.
 * - Associates the destroy() callback.
 *
 * Role:
 * Converts each substring from the splitter into a complete token,
 * preserving position, types, and necessary metadata.
 */
static t_lexer	*ft_create_lexer(
								const char *prompt,
								t_splited_prompt **split,
								t_expander_callbacks callbacks)
{
	t_lexer		*tk_prompt;
	t_token		**curr_token;

	tk_prompt = ft_calloc(1, sizeof(t_lexer));
	if (!tk_prompt)
		return (NULL);
	tk_prompt->size = (*split)->len;
	tk_prompt->original_prompt = (const char *)ft_strdup(prompt);
	tk_prompt->tokens = ft_calloc((*split)->len + 1, sizeof(t_token *));
	while (--(*split)->len >= 0)
	{
		curr_token = &tk_prompt->tokens[(*split)->len];
		*curr_token = ft_tokenize((*split)->chuncks[(*split)->len],
				(*split)->len, (*split)->coords[(*split)->len], callbacks);
		if (!*curr_token)
		{
			(*split)->destroy(split);
			return (ft_destroy_lexer(&tk_prompt));
		}
	}
	(*split)->destroy(split);
	tk_prompt->destroy = ft_destroy_lexer;
	return (tk_prompt);
}

/**
 * # ft_destroy_lexer
 *
 * Complete destructor for t_lexer structure.
 *
 * Logic:
 * - Frees the copied original prompt.
 * - Iterates over the token array in reverse:
 *       - Calls token->destroy() for each token.
 * - Frees the token array.
 * - Frees the t_lexer structure itself.
 * - Sets external pointer to NULL.
 *
 * Role:
 * Ensures total cleanup of the token tree,
 * preventing any memory leaks.
 */
static void	*ft_destroy_lexer(t_lexer	**self_ref)
{
	t_lexer	*self;

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
