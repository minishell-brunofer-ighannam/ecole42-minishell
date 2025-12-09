/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:38:47 by valero            #+#    #+#             */
/*   Updated: 2025/12/09 18:23:58 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLITTER_H
# define SPLITTER_H

/**
 * # t_splited_prompt
 *
 * Structure representing the final result
 * of the splitter.
 * Stores:
 * - `chuncks`: array of extracted substrings.
 * - `coords`: {start, end} pairs in the
 *   original string.
 * - `len`: number of tokens.
 * - `destroy`: callback to free the structure.
 *
 * This is the final object returned to the user.
 */
typedef struct s_splited_prompt	t_splited_prompt;
struct s_splited_prompt
{
	char	**chuncks;
	int		**coords;
	int		len;
	void	*(*destroy)(t_splited_prompt **self_ref);
};

t_splited_prompt	*ft_splitter(char const *str);

#endif
