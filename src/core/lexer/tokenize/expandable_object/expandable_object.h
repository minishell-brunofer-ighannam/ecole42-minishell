/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable_object.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:05:39 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 03:44:11 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDABLE_OBJECT_H
# define EXPANDABLE_OBJECT_H

# include <stdbool.h>

/**
 * # t_token
 *
 * Representa um token já classificado e apto a expansão.
 * Campos:
 * - value: string original do token.
 * - type: tipo classificado via ft_get_token_type().
 * - position: índice do token na linha original.
 * - coord_in_src: coordenadas de início/fim na string original.
 * - sintaxe_error: erro sintático detectado.
 * - feature_out_of_scope: indica recursos ainda não suportados.
 * - last_build: cache da expansão realizada (para evitar refazer).
 * - expand_var: callback para expansão de variáveis.
 * - expand_glob: callback para expansão glob.
 * - build_expansion: função que executa toda a lógica de expansão.
 * - destroy: destrói o token.
 * - expandable_object: dados sobre o que pode ser expandido.
 */
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
