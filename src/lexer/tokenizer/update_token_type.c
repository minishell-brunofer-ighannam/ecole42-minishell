/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:28:06 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/06 14:35:31 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static t_token	*ft_simulate_token(char **words, int idx, int right);
static void		ft_update_cmd_token_type(t_token *token, char **words, int idx);

void	ft_update_token_type(t_token *token, char **words, int idx)
{
	int		len_word;

	len_word = ft_strlen(words[idx]);
	ft_build_generic_token_types(token, words, idx, len_word);
	ft_update_cmd_token_type(token, words, idx);
}

/**
 * # ft_simulate_token
 *
 * ---
 *
 * Creates a temporary token simulating either the previous or next word
 * in the command sequence, based on the specified direction.
 *
 * This function is used to inspect the type of a neighboring token
 * without modifying the real token list. It allocates a temporary
 * `t_token`, classifies it using `ft_build_generic_token_types()`,
 * and returns it for contextual analysis (e.g. syntax validation or
 * command-type inference).
 *
 * ## Logic
 * - If `right` is **true (1)**:
 *   - Simulates the token at `words[idx + 1]`.
 *   - Returns `NULL` if there is no next word.
 * - If `right` is **false (0)**:
 *   - Simulates the token at `words[idx - 1]`.
 *   - Returns `NULL` if there is no previous word (`idx == 0`).
 *
 * ## Parameters
 * - `words`: Array of strings representing parsed command words.
 * - `idx`: Current index in the array `words`.
 * - `right`: Direction flag — `1` to simulate the next token, `0` for the previous.
 *
 * ## Returns
 * - A pointer to a newly allocated `t_token` representing the simulated word.
 * - `NULL` if the neighboring word does not exist.
 *
 * ## Notes
 * - The returned token is **dynamically allocated** and must be freed
 *   by the caller.
 * - The simulated token is independent and not linked to any real token list.
 * - This function is typically used by parsing helpers that need to
 *   analyze the syntactic context around a given token.
 */
static t_token	*ft_simulate_token(char **words, int idx, int right)
{
	int		len_word;
	t_token	*sim_token;

	len_word = ft_strlen(words[idx]);
	if (right)
	{
		if (!words[idx + 1])
			return (NULL);
		sim_token = ft_calloc(1, sizeof(t_token));
		ft_build_generic_token_types(sim_token, words, idx + 1, len_word);
		return (sim_token);
	}
	if (!idx)
		return (NULL);
	sim_token = ft_calloc(1, sizeof(t_token));
	ft_build_generic_token_types(sim_token, words, idx - 1, len_word);
	return (sim_token);
}

/**
 * # ft_update_cmd_token_type
 *
 * ---
 *
 * Reclassifies a token as `TOKEN_CMD` when its position in the command
 * sequence indicates the start of a new command.
 *
 * This function uses `ft_simulate_token()` to inspect the token immediately
 * to the left of the current one. If that left token is an operator that
 * begins a new command context — such as a pipe, logical operator, or an
 * opening parenthesis — and the current token is not a reserved operator,
 * it updates the token type to `TOKEN_CMD`.
 *
 * ## Logic
 * - Simulates the **left token** using `ft_simulate_token(words, idx, 0)`.
 * - If the current token is **not** a reserved operator (`is_reserved_token_type` returns false),
 *   and the left token exists and is one of:
 *   - `TOKEN_PIPE` (`|`)
 *   - `TOKEN_OR` (`||`)
 *   - `TOKEN_AND` (`&&`)
 *   - `TOKEN_PAREN_OPEN` (`(`)
 *   → Then, the current token is reclassified as a **command** (`TOKEN_CMD`).
 *
 * ## Parameters
 * - `token`: Pointer to the current token to be updated.
 * - `words`: Array of strings representing parsed words from the input line.
 * - `idx`: Index of the current token within `words`.
 *
 * ## Notes
 * - The left token is created temporarily via `ft_simulate_token()` and freed before returning.
 * - This function does not alter `words`, only updates `token->type`.
 * - It ensures syntactic consistency, marking new command beginnings
 *   after operators like `|`, `||`, `&&`, or `(`.
 */
static void	ft_update_cmd_token_type(t_token *token, char **words, int idx)
{
	t_token	*left_token;

	left_token = ft_simulate_token(words, idx, 0);
	if (!is_reserved_token_type(token) && left_token
		&& (left_token->type == TOKEN_PIPE
			|| left_token->type == TOKEN_OR || left_token->type == TOKEN_AND
			|| left_token->type == TOKEN_PAREN_OPEN))
		token->type = TOKEN_CMD;
	free(left_token);
}

static void	ft_update_arg_token_type(t_token *token, char **words, int idx)
{
	t_token	*left_token;

	left_token = ft_simulate_token(words, idx, 0);
	if (!is_reserved_token_type(token)
		&& left_token && (is_reserved_token_type(left_token)
			|| (left_token->type == TOKEN_CMD)))
		token->type = TOKEN_ARG;
	free(left_token);
}
