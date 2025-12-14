/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:58:37 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/14 16:18:11 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdbool.h>
# include "./expandable_object/expandable_object.h"
# include "../../../data_structures/data_structures.h"
# include "separate_quote_chuncks/separate_quote_chuncks.h"

/**
 * # t_token_type
 *
 * Compact enum representing token types.
 * Each item combines chars using bit-shifts to allow
 * fast identification and direct integer comparison.
 *
 * Logic:
 * - 1-char tokens use the character directly.
 * - 2-char tokens use (c1 << 8 | c2).
 * - TOKEN_UNKNOWN uses 'u''n''k' packed as an integer.
 */
typedef enum e_token_type			t_token_type;
enum e_token_type
{
	TOKEN_UNKNOWN = 'u' << 16 | 'n' << 8 | 'k',
	TOKEN_CMD = 'c' << 16 | 'm' << 8 | 'd',
	TOKEN_ARG = 'a' << 16 | 'r' << 8 | 'g',
	TOKEN_PIPE = '|',
	TOKEN_OR = '|' << 8 | '|',
	TOKEN_AND = '&' << 8 | '&',
	TOKEN_SEMICOLON = ';',
	TOKEN_BACKGROUND = '&',
	TOKEN_PAREN_OPEN = '(',
	TOKEN_PAREN_CLOSE = ')',
	TOKEN_REDIRECT_IN = '<',
	TOKEN_REDIRECT_OUT = '>',
	TOKEN_HERE_DOC_IN = '<' << 8 | '<',
	TOKEN_APPEND_OUT = '>' << 8 | '>',
	TOKEN_REDIRECT_IN_OUT = '<' << 8 | '>',
	TOKEN_REDIRECT_FORCE_OUT = '>' << 8 | '|',
	TOKEN_REDIRECT_ERR_OUT = '2' << 8 | '>',
	TOKEN_REDIRECT_OUT_ERR = '&' << 8 | '>',
	TOKEN_REDIRECT_OUT_MERGE = '>' << 8 | '&',
	TOKEN_END = '\0'
};

/**
 * # t_expansion_build
 *
 * Stores the final result of a variable/glob expansion.
 * Contains:
 * - glob_error: message if glob expansion failed.
 * - token_expanded: final token without quotes and with expansions applied.
 * - destroy: frees the structure.
 */
typedef struct s_expansion_build	t_expansion_build;
struct s_expansion_build
{
	char	*glob_error;
	char	*token_expanded;
	void	*(*destroy)(t_expansion_build **self_ref);
};

/**
 * # t_token
 *
 * Represents a token already classified and ready for expansion.
 * Fields:
 * - value: original token string.
 * - type: classified type via ft_get_token_type().
 * - position: token index in the original line.
 * - coord_in_src: start/end coordinates in the original string.
 * - syntax_error: detected syntax error.
 * - feature_out_of_scope: indicates unsupported features.
 * - last_build: cache of the expansion performed (avoids recomputation).
 * - expand_var: callback for variable expansion.
 * - expand_glob: callback for glob expansion.
 * - build_expansion: function executing the full expansion logic.
 * - destroy: destroys the token.
 * - expandable_object: data about what can be expanded.
 */
typedef struct s_token				t_token;
struct s_token
{
	const char			*value;
	t_expansion_build	*last_build;
	t_token_type		type;
	int					position;
	int					*coord_in_src;
	bool				sintaxe_error;
	bool				feature_out_of_scope;
	char				*(*remove_quotes)(t_token *self);
	char				*(*expand_var)(
			const char *token, t_linkedlist_array *ht_env);
	char				**(*expand_glob)(const char *token);
	t_expansion_build	*(*build_expansion)(
			t_token *self, t_linkedlist_array *ht_env);
	void				*(*destroy)(t_token **self_ref);
	t_expandable_object	*expandable_object;
};

typedef char						*(*t_expand_var_clbk)(const char *token,
										t_linkedlist_array *ht_env);
typedef char						**(*t_expand_glob_clbk)(
										const char *token);
/**
 * # t_expander_callbacks
 *
 * Stores the necessary callbacks:
 * - expand_var: variable → expanded string
 * - expand_glob: glob → list of strings
 */
typedef struct s_expander_callbacks	t_expander_callbacks;
struct s_expander_callbacks
{
	t_expand_var_clbk	expand_var;
	t_expand_glob_clbk	expand_glob;
};

t_token					*ft_tokenize(
							const char *chunck,
							int idx,
							int *coord_in_src,
							t_expander_callbacks callbacks);

t_expander_callbacks	ft_create_expander_callbacks(
							t_expand_var_clbk	expand_var,
							t_expand_glob_clbk	expand_glob);

#endif
