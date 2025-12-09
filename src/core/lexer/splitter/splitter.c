/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:36:19 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:23:26 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

/**
 * # ft_splitter
 *
 * High-level function that unifies the
 * entire flow: takes the raw string,
 * performs full refinement, and returns
 * the final `t_splited_prompt`.
 *
 * Role:
 * - Serves as a simple interface for the user.
 * - Encapsulates internal logic
 *   (`ft_raw_splitter` + refinement).
 * - Ensures it always returns only the
 *   final filtered result.
 *
 * Note:
 * Does not implement any logic itself —
 * delegates everything to
 * `ft_refined_splitter`, which manages
 * the full process.
 */
t_splited_prompt	*ft_splitter(char const *str)
{
	t_splited_prompt	*splitted;

	splitted = ft_refined_splitter(str);
	return (splitted);
}
