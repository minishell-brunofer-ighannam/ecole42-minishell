/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable_object.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:05:39 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:27:27 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDABLE_OBJECT_H
# define EXPANDABLE_OBJECT_H

# include <stdbool.h>

/**
 * # t_token
 *
 * Represents a token that is already classified
 * and ready for expansion.
 *
 * Fields:
 * - `value`: original token string.
 * - `type`: type classified via
 *   `ft_get_token_type()`.
 * - `position`: token index in the original line.
 * - `coord_in_src`: start/end coordinates in
 *   the original string.
 * - `sintaxe_error`: detected syntax error.
 * - `feature_out_of_scope`: indicates
 *   unsupported features.
 * - `last_build`: cache of performed expansion
 *   (to avoid redoing).
 * - `expand_var`: callback for variable expansion.
 * - `expand_glob`: callback for glob expansion.
 * - `build_expansion`: function executing all
 *   expansion logic.
 * - `destroy`: destroys the token.
 * - `expandable_object`: data about what
 *   can be expanded.
 */
typedef struct s_token				t_token;

/**
 * # t_expandable_object
 *
 * Final structure delivered to the expansion
 * module.
 *
 * Stores:
 * - `original_value`: original token value.
 * - `expanded_value`: expansion without glob.
 * - `expanded_glob_value`: expansion with
 *   glob applied.
 * - `expandable_keys`: array of found keys
 *   ($USER, $?).
 * - `expandable_coord_keys`: original
 *   coordinates of these keys.
 * - `has_globs`: marks if any key contains `*`
 *   outside quotes.
 * - `expanded_chuncks`: substrings resulting
 *   from the expansion.
 *
 * This is the object that the minishell
 * actually uses to substitute values.
 */
typedef struct s_expandable_object	t_expandable_object;
struct s_expandable_object
{
	const char			*original_value;
	char				*expanded_value;
	char				*expanded_glob_value;
	bool				has_globs;
	char				**expandable_keys;
	int					**expandable_coord_keys;
	char				**expanded_chuncks;
	void				*(*destroy)(t_expandable_object **self_ref);
};

t_expandable_object	*ft_create_expandable_object(t_token *token);

#endif
