/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:14:45 by valero            #+#    #+#             */
/*   Updated: 2025/11/05 16:05:46 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>

/**
 * # Token Type
 *
 * ---
 *
 * Defines the possible categories of tokens recognized by the lexer.
 * Each token type represents a specific syntactic element that can appear
 * in a command line.
 *
 * - `TOKEN_CMD`: A command name (e.g., `echo`, `ls`, `cat`).
 * - `TOKEN_ARG`: A command argument or parameter.
 * - `TOKEN_PIPE`: A pipe operator (`|`) connecting commands.
 * - `TOKEN_OR`: A logical OR operator (`||`).
 * - `TOKEN_AND`: A logical AND operator (`&&`).
 * - `TOKEN_REDIRECT_IN`: Input redirection operator (`<`).
 * - `TOKEN_REDIRECT_OUT`: Output redirection operator (`>`).
 * - `TOKEN_HERE_DOC_IN`: Here-document input operator (`<<`).
 * - `TOKEN_HERE_DOC_OUT`: Here-document output operator (`>>`).
 * - `TOKEN_PAREN_OPEN`: Opening parenthesis (`(`), usually for subshells or grouping.
 * - `TOKEN_PAREN_CLOSE`: Closing parenthesis (`)`).
 * - `TOKEN_END`: Marks the end of the token list or input stream.
 */
typedef enum e_token_type {
	TOKEN_CMD,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HERE_DOC_IN,
	TOKEN_HERE_DOC_OUT,
	TOKEN_PAREN_OPEN,
	TOKEN_PAREN_CLOSE,
	TOKEN_END
}	t_token_type;

/**
 * # Quote Type
 *
 * ---
 *
 * Represents the type of quotation that affects how a token is parsed
 * and expanded in the shell.
 *
 * - `QUOTE_NONE`: No quotation applied; normal parsing and expansions occur.
 * - `QUOTE_SINGLE`: Single quotes (`'...'`) — literal mode, no variable or command expansion.
 * - `QUOTE_DOUBLE`: Double quotes (`"..."`) — allows variable expansion, but prevents word splitting.
 */
typedef enum e_quote_type {
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

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
 *     The original, unmodified input string (e.g. "ola $USER ... $HOME/\*").
 *
 * - `expanded_value`:
 *     Result after performing variable expansions only (e.g. "$HOME" -> "/home/bruno"),
 *     but before any globbing is applied.
 *
 * - `expanded_glob_value`:
 *     Result after applying glob expansion to `expanded_value` (e.g. "/home/bruno/\*"
 *     -> "/home/bruno/file1 /home/bruno/dir1"). May be NULL if no globbing was needed
 *     or if glob expansion failed.
 *
 * - `idx_expandable_chuncks`:
 *     An array of index-pairs (e.g. `[[start0, end0], [start1, end1], ...]`) that mark
 *     the positions of each expandable substring inside `original_value`. Index pairs
 *     use inclusive start and exclusive end (start, end) convention.
 *
 * - `expandable_chuncks`:
 *     Array of the expandable substrings extracted from `original_value` that represent
 *     **variable** expansions only (e.g. `["$USER", "$HOME", "$$", "$HOME"]`). Globs
 *     (like "/\*") are NOT included here. Order corresponds to `idx_expandable_chuncks`.
 *
 * - `expanded_chuncks`:
 *     Array of the corresponding expanded results for each entry in `expandable_chuncks`
 *     (e.g. ["bruno", "/home/bruno", "12345", "/home/bruno"]). Order matches
 *     `expandable_chuncks` and `idx_expandable_chuncks`.
 *
 *Notes:
 * - `expandable_chuncks` and `expanded_chuncks` are parallel arrays and must have the
 *   same length as `idx_expandable_chuncks`.
 * - Any pointer field may be NULL when not applicable (e.g., no variables present,
 *   no glob patterns, or expansion error).
 * - The field name `*_chuncks` contains a spelling inconsistency; consider renaming to
 *   `*_chunks` for clarity if you are free to change the API.
 */
typedef struct s_expandable_object {
	const char	*original_value;
	char		*expanded_value;
	char		*expanded_glob_value;
	int			**idx_expandable_chuncks;
	char		**expandable_chuncks;
	char		**expanded_chuncks;
}	t_expandable_object;

/**
 * # Token
 *
 * ---
 *
 * Represents a single lexical unit (token) extracted from the command line.
 * Each token contains information about its textual value, syntactic type,
 * quoting style, and possible expandability context.
 *
 * Fields:
 * - `value`:
 *     The literal text of the token as parsed from the input line.
 *     This string remains unmodified (not expanded).
 *
 * - `type`:
 *     The syntactic classification of the token (see `t_token_type`),
 *     such as command, argument, operator, or redirection.
 *
 * - `position`:
 *     The position of this token in the token list or input stream.
 *     Used for maintaining execution order and syntax diagnostics.
 *
 * - `arg_index`:
 *     The position of this token among the arguments of a command.
 *     Applies only when `type == TOKEN_ARG`.
 *
 * - `valid`:
 *     Boolean flag indicating whether this token was recognized as valid
 *     by the lexer. Invalid tokens can signal syntax or parsing errors.
 *
 * - `is_expandable`:
 *     Indicates whether this token **may allow expansion**, based solely on its
 *     syntactic and quoting context.
 *     It is set to `true` only when:
 *       - `type == TOKEN_ARG`, and
 *       - the token is either unquoted or enclosed in double quotes.
 *     The presence or absence of actual expandable sections is managed
 *     by `expandable_object`, not by this flag.
 *
 * - `expandable_object`:
 *     Holds metadata and values related to the token’s variable and glob
 *     expansions (see `t_expandable_object`).
 *
 * - `quote_type`:
 *     Specifies how the token is quoted (none, single, or double). This affects
 *     how expansions and parsing rules are applied.
 *
 * Notes:
 * - `value` remains immutable and serves as the canonical text reference.
 * - Expansions are processed through `expandable_object` only if the token is
 *   eligible for expansion (`is_expandable == true`).
 */
typedef struct s_token {
	const char				*value;
	t_token_type			type;
	int						position;
	int						arg_index;
	bool					valid;
	bool					is_expandable;
	t_expandable_object		expandable_object;
	t_quote_type			quote_type;
}	t_token;

#endif
