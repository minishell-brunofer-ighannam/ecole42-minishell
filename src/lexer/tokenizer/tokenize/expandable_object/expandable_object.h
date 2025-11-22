/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable_object.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:05:39 by valero            #+#    #+#             */
/*   Updated: 2025/11/22 15:10:14 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDABLE_OBJECT_H
# define EXPANDABLE_OBJECT_H

# include <stdbool.h>

typedef struct s_token				t_token;

/**
 * # t_expandable_object
 *
 * Estrutura final entregue para o módulo de expansão.
 *
 * Armazena:
 * - `original_value`: valor original do token.
 * - `expanded_value`: expansão sem glob.
 * - `expanded_glob_value`: expansão com glob aplicado.
 * - `expandable_keys`: array de chaves encontradas ($USER, $?).
 * - `expandable_coord_keys`: coordenadas originais dessas chaves.
 * - `has_globs`: marca se alguma chave contém `*` fora de aspas.
 * - `expanded_chuncks`: substrings resultantes após expansão.
 *
 * É o objeto que o minishell realmente usa para substituir valores.
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
