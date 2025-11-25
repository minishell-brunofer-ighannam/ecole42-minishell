/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:38:47 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 21:41:48 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLITTER_H
# define SPLITTER_H

/**
 * # t_splited_prompt
 *
 * Estrutura que representa o resultado final do splitter.
 * Armazena:
 * - `chuncks`: array de substrings extraídas.
 * - `coords`: pares {start, end} no string original.
 * - `len`: número de tokens.
 * - `destroy`: callback para liberar a estrutura.
 *
 * É o objeto final retornado ao usuário.
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
