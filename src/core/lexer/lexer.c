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

t_lexer			*ft_creater_lexer_error(t_lexer_error error);
static bool		ft_isempty(const char *prompt);
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

	if (!prompt || !*prompt || ft_isempty(prompt))
		return (NULL);
	error_idx = ft_prompt_validator(prompt);
	if (error_idx > -1)
	{
		ft_print_structure_not_closed_error(prompt, error_idx);
		return (ft_creater_lexer_error(LEXER_ERROR_STRUCTURE_NOT_CLOSED));
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
	t_lexer		*lexer;
	t_token		**curr_token;

	lexer = ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->size = (*split)->len;
	lexer->original_prompt = (const char *)ft_strdup(prompt);
	lexer->tokens = ft_calloc((*split)->len + 1, sizeof(t_token *));
	while (--(*split)->len >= 0)
	{
		curr_token = &lexer->tokens[(*split)->len];
		*curr_token = ft_tokenize(prompt, (*split)->len,
				(*split)->coords[(*split)->len], callbacks);
		if (!*curr_token)
		{
			(*split)->destroy(split);
			return (ft_destroy_lexer(&lexer));
		}
	}
	(*split)->destroy(split);
	lexer->destroy = ft_destroy_lexer;
	return (lexer);
}

t_lexer	*ft_creater_lexer_error(t_lexer_error error)
{
	t_lexer		*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->error = error;
	lexer->destroy = ft_destroy_lexer;
	return (lexer);
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

static bool	ft_isempty(const char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
		if (!((prompt[i] >= 9 && prompt[i] <= 13) || prompt[i] == 32))
			return (false);
	return (true);
}
