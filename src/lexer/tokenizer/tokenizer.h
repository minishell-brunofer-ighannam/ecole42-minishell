/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:26:23 by valero            #+#    #+#             */
/*   Updated: 2025/11/06 18:59:21 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "libft.h"
# include "../../linkedlist/linkedlist.h"
# include <stdbool.h>

/**
 * # Token Type
 *
 * ---
 *
 * Defines all possible categories of tokens recognized by the lexer.
 * Each token type corresponds to a syntactic element that can appear
 * in a shell command line.
 *
 * ## Command and Arguments
 * - `TOKEN_CMD`: A command name (e.g., `echo`, `ls`, `cat`).
 * - `TOKEN_ARG`: A command argument or parameter.
 *
 * ## Logical Operators
 * - `TOKEN_PIPE`: Pipe operator (`|`) connecting commands.
 * - `TOKEN_OR`: Logical OR operator (`||`).
 * - `TOKEN_AND`: Logical AND operator (`&&`).
 *
 * ## Control and Grouping
 * - `TOKEN_SEMICOLON`: Command separator (`;`).
 * - `TOKEN_BACKGROUND`: Background execution operator (`&`).
 * - `TOKEN_PAREN_OPEN`: Opening parenthesis (`(`),
 *		used for subshells or grouping.
 * - `TOKEN_PAREN_CLOSE`: Closing parenthesis (`)`).
 *
 * ## Redirections
 * - `TOKEN_REDIRECT_IN`: Input redirection (`<`).
 * - `TOKEN_REDIRECT_OUT`: Output redirection (`>`).
 * - `TOKEN_HERE_DOC_IN`: Here-document input (`<<`).
 * - `TOKEN_APPEND_OUT`: Append output (`>>`).
 * - `TOKEN_REDIRECT_IN_OUT`: Input/output redirection (`<>`).
 * - `TOKEN_REDIRECT_FORCE_OUT`: Redirect stdout and append (`>|`).
 * - `TOKEN_REDIRECT_ERR_OUT`: Redirect stderr to file (`2>`).
 * - `TOKEN_REDIRECT_OUT_ERR`: Redirect stdout and stderr together (`&>`).
 *
	- `TOKEN_REDIRECT_OUT_MERGE`: Redirect stdout to another
 *	file descriptor (`>&`).
 *
 * ## Misc
 * - `TOKEN_END`: Marks the end of the token list or input stream.
 */
typedef enum e_token_type
{
	// 099109100
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
}						t_token_type;

/**
 * # Quote Type
 *
 * ---
 *
 * Represents the type of quotation that affects how a token is parsed
 * and expanded in the shell.
 *
 * - `QUOTE_NONE`: No quotation applied; normal parsing and expansions occur.
 * - `QUOTE_SINGLE`: Single quotes (`'...'`) — literal mode, no variable or
 * command expansion.
 * - `QUOTE_DOUBLE`: Double quotes (`"..."`) — allows variable expansion,
 * but prevents word splitting.
 */
typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}						t_quote_type;

/**
 * # Expandable Object
 *
 * ---
 *
 * Represents a source string that may contain variable and glob expansions.
 * Keeps the original text plus intermediate and final expansion results, and
 * tracks exactly which substrings were variable-expandable and where they live
 * inside the original string.
 *
 * Fields:
 * - `original_value`:
 *		The original, unmodified input string (e.g. "ola $USER ... $HOME/\*").
 *
 * - `expanded_value`:
 *		Result after performing variable expansions only
 *		(e.g. "$HOME" -> "/home/bruno"), but before any globbing is applied.
 *
 * - `expanded_glob_value`:
 *		Result after applying glob expansion to `expanded_value`
 *		(e.g. "/home/bruno/\*" -> "/home/bruno/file1 /home/bruno/dir1").
 *		May be NULL if no globbing was needed or if glob expansion failed.
 *
 * - `idx_expandable_chuncks`:
 *		An array of index-pairs (e.g. `[[start0, end0], [start1, end1], ...]`)
 *		that mark the positions of each expandable substring inside
 *		`original_value`. Index pairs use inclusive start and exclusive end
 * 		(start, end) convention.
 *
 * - `expandable_chuncks`:
 *		Array of the expandable substrings extracted from `original_value`
 *		that represent **variable** expansions only
 *		(e.g. `["$USER", "$HOME", "$$", "$HOME"]`). Globs (like "/\*") are NOT
		included here. Order corresponds to `idx_expandable_chuncks`.
 *
 * - `expanded_chuncks`:

			*		Array of the corresponding expanded results for each entry in `expandable
 *		_chuncks` (e.g. `["bruno", "/home/bruno", "12345", "/home/bruno"]`).
 *		Order matches `expandable_chuncks` and `idx_expandable_chuncks`.

 *
 *Notes:
 * - `expandable_chuncks` and `expanded_chuncks` are parallel arrays and
 *   must have the same length as `idx_expandable_chuncks`.
 * - Any pointer field may be NULL when not applicable (e.g., no variables
 *   present, no glob patterns, or expansion error).
 * - The field name `*_chuncks` contains a spelling inconsistency; consider
 *   renaming to `*_chunks` for clarity if you are free to change the API.
 */
typedef struct s_expandable_object
{
	const char			*original_value;
	char				*expanded_value;
	char				*expanded_glob_value;
	int					**idx_expandable_chuncks;
	char				**expandable_chuncks;
	char				**expanded_chuncks;
}						t_expandable_object;

/**
 * # Token
 *
 * ---
 *
 * Represents a single lexical unit (token) extracted from the command line.
 * Each token contains information about its text, syntactic classification,
 * quoting, expansion eligibility, and validation status.
 *
 * Fields:
 * - `value`:
 *		The literal,
			immutable string of the token as parsed from the input line.
 *		This pointer must never be modified; it refers to the original command.
 *
 * - `type`:
 *		The syntactic category of the token (see `t_token_type`),
 *		such as command, argument, operator, or redirection.
 *
 * - `position`:
 *		The index of this token in the token list or input stream.
 *		Useful for maintaining parsing order and for detailed error messages.
 *
 * - `arg_index`:
 *		The argument index within a command, starting from zero.
 *		Relevant only when `type == TOKEN_ARG`.
 *
 * - `sintaxe_error`:
 *		Indicates whether a syntax error was detected in this token.
 *		Examples include unclosed quotes, misplaced operators, or invalid
 *		sequences. When `true`, parsing or execution should handle this
 *		token as erroneous.
 *
 * - `feature_out_of_scope`:
 *		Marks tokens that represent valid shell syntax but belong to features
 *		intentionally excluded from the Minishell project scope.
 *		Example: command substitution (`$(command)`), arithmetic expansion, etc.
 *		When `true`, the parser should report the feature as unsupported
 *		rather than invalid.
 *
 * - `is_expandable`:
 *		Indicates whether this token *may allow expansion*, based on context.
 *		It is set to `true` only when:
 *			- `type == TOKEN_ARG`, and
 *			- the token is either unquoted or double-quoted.
 *		This flag does not guarantee the presence of expandable content; that is
 *		determined through the `expandable_object`.
 *
 * - `expandable_object`:
 *		Stores metadata and values related to variable or glob expansions
 *		within this token (see `t_expandable_object`).
 *
 * - `quote_type`:
 *		Indicates the quoting context applied to this token
 *		(none, single, or double). Quoting affects how expansions
 *		and parsing rules are interpreted.
 *
 * Notes:
 * - `value` must be treated as read-only (`const`).
 * - `sintaxe_error` and `feature_out_of_scope` are mutually exclusive in logic:
 *   a token cannot be both syntactically invalid and
 *   a valid but unsupported feature.
 * - Expansions should only be attempted if `is_expandable` is true.
 */
typedef struct s_token
{
	const char			*value;
	t_token_type		type;
	int					position;
	int					arg_index;
	bool				sintaxe_error;
	bool				feature_out_of_scope;
	bool				is_expandable;
	t_expandable_object	expandable_object;
	t_quote_type		quote_type;
}						t_token;

/**
 * # Token Group
 *
 * ---
 *
 * Represents a full input line that has been tokenized into individual tokens.
 *
 * Each token group therefore corresponds to one complete shell command line
 * ready for parsing and execution.
 *
 * Fields:
 *
 * - `tokens`:
 *		A NULL-terminated array of pointers to `t_token` structures.
 *		Each entry represents a single lexical token parsed from the input line.
 *		The final element is always `NULL`, allowing safe iteration.
 *
 * - `size`:
 *		The number of tokens contained in `tokens` (excluding the final NULL).
 *		Useful for iteration, debugging, and validation.
 *
 * Notes:
 * - A `t_token_group` represents exactly one shell command line — the portion
 *   of input between two newline characters.
 * - The newline (`\n`) is used only as a delimiter and is **not** stored in
 *   any token value.
 * - Memory ownership rules should remain consistent: the group owns the
 *   `tokens` array, but each individual `t_token` is managed by the lexer.
 * - Both the NULL terminator and the `size` field can be used for iteration,
 *   depending on style and performance needs.
 */
typedef struct s_token_group
{
	t_token				**tokens;
	int					size;
}						t_token_group;


char	**ft_major_token_split(char const *s);
void	ft_build_generic_token_types(
			t_token *token, char **words, int idx, int len_word);
bool	is_reserved_token_type(t_token *token);
void	ft_update_token_type(t_token *token, char **words,
			int idx);
void	ft_update_token_metadata(t_token *token, char **words,
			int idx);

#endif
