/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:31:12 by valero            #+#    #+#             */
/*   Updated: 2025/11/06 23:48:00 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/**
 * # ft_build_generic_token_types
 *
 * ---
 *
 * Determines and assigns the token type based on the content of a word.
 * This function analyzes a given word extracted from the command line
 * and classifies it as a specific token according to its syntax and position.
 *
 * ## Logic
 * - If it is the first word (`idx == 0`), it is treated as a command (`TOKEN_CMD`).
 * - If the token is inside quotes, it is treated as an argument (`TOKEN_ARG`).
 * - If it matches a single-character operator (`| ( ) < > ; &`), it is
 *   classified by that character directly.
 * - If it matches a two-character operator, the type is built by combining
 *   both characters (`char0 << 8 | char1`), recognizing patterns such as:
 *   - `||`, `&&` — logical operators
 *   - `<<`, `>>`, `<>` — redirections
 *   - `>|`, `&>`, `2>` — special redirections
 * - Otherwise, it defaults to an argument (`TOKEN_ARG`).
 *
 * ## Parameters
 * - `token`: Pointer to the token structure to be filled.
 * - `words`: Array of parsed strings representing each separated word.
 * - `idx`: Current index within the array of words.
 * - `len_word`: Length of the current word.
 *
 * This function does not allocate memory or modify the input strings;
 * it only assigns the correct `token->type` value for later parsing stages.
 */
void	ft_build_generic_token_types(
	t_token *token, char **words, int idx, int len_word)
{
	int	char0;

	char0 = words[idx][0];
	if (idx == 0)
		token->type = TOKEN_CMD;
	else if (token->quote_type != QUOTE_NONE)
		token->type = TOKEN_ARG;
	else if (len_word == 1 && ft_strchr("|()<>;&", char0))		// | ( ) < > ; &
		token->type = char0;
	else if (len_word == 2 && (
			(char0 == '>' && ft_strchr("|&>", words[idx][1]))	// >| >& >>
		|| (char0 == '&' && ft_strchr("&>", words[idx][1]))		// && &>
		|| (char0 == '<' && ft_strchr("<>", words[idx][1]))	// << <>
		|| (char0 == '|' && words[idx][1] == '|')				// ||
		|| (char0 == '2' && words[idx][1] == '>')))				// 2>
		token->type = char0 << 8 | words[idx][1];
	else
		token->type = TOKEN_ARG;
}

/**
 * # is_reserved_token_type
 *
 * ---
 *
 * Checks whether a given token corresponds to a reserved operator type
 * used by the shell syntax.
 *
 * Reserved tokens include logical, control, and redirection operators
 * that affect command flow or I/O behavior. This function helps
 * distinguish between syntactic operators and regular words such as
 * commands or arguments.
 *
 * ## Returns
 * - `true`  → if the token represents a reserved operator (e.g. `|`, `&&`, `;`, `<`, `>`, etc.).
 * - `false` → if it represents a command, argument, or any non-operator token.
 *
 * ## Examples
 * - `&&`, `||`, `|`, `&` → logical/pipe operators
 * - `<`, `>`, `<<`, `>>`, `>|`, `2>`, `&>`, `>&`, `<>` → redirection operators
 * - `;` → command separator
 * - `(`, `)` → subshell grouping
 *
 * ## Parameters
 * - `token`: Pointer to the token whose type will be checked.
 *
 * ## Notes
 * This function does not modify the token or perform any parsing.
 * It is typically used by the parser to identify control structures
 * or enforce syntactic validation.
 */
bool	is_reserved_token_type(t_token *token)
{
	t_token_type	type;

	type = token->type;
	return (type == TOKEN_AND || type == TOKEN_OR								// && ||
		|| type == TOKEN_PIPE || type == TOKEN_BACKGROUND						// | &
		|| type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT				// < >
		|| type == TOKEN_HERE_DOC_IN || type == TOKEN_APPEND_OUT				// << >>
		|| type == TOKEN_REDIRECT_FORCE_OUT || type == TOKEN_REDIRECT_ERR_OUT	// >| 2>
		|| type == TOKEN_REDIRECT_OUT_ERR || type == TOKEN_REDIRECT_OUT_MERGE	// &> >&
		|| type == TOKEN_REDIRECT_IN_OUT || type == TOKEN_SEMICOLON				// <> ;
		|| type == TOKEN_PAREN_OPEN || type == TOKEN_PAREN_CLOSE				// ( )
		);
}

bool	can_have_args(t_token *token)
{
	t_token_type	type;

	type = token->type;
	return (type == TOKEN_CMD || type == TOKEN_OR								// && ||
		|| type == TOKEN_PIPE || type == TOKEN_BACKGROUND						// | &
		|| type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT				// < >
		|| type == TOKEN_HERE_DOC_IN || type == TOKEN_APPEND_OUT				// << >>
		|| type == TOKEN_REDIRECT_FORCE_OUT || type == TOKEN_REDIRECT_ERR_OUT	// >| 2>
		|| type == TOKEN_REDIRECT_OUT_ERR || type == TOKEN_REDIRECT_OUT_MERGE	// &> >&
		|| type == TOKEN_REDIRECT_IN_OUT || type == TOKEN_SEMICOLON				// <> ;
		|| type == TOKEN_PAREN_OPEN || type == TOKEN_PAREN_CLOSE				// ( )
		);
}
