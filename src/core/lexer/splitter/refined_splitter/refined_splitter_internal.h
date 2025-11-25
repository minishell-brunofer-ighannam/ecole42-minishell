/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_splitter_internal.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:21:30 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 23:13:37 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFINED_SPLITTER_INTERNAL_H
# define REFINED_SPLITTER_INTERNAL_H

# include "../../../../data_structures/data_structures.h"
# include "../../lexer_internal.h"
# include "../splitter_internal.h"
# include "../raw_splitter/raw_splitter.h"

/**
 * # t_refine_raw_token_vars
 *
 * Variáveis internas usadas durante o refinamento de um token bruto.
 * Mantém estado do parsing: posição atual, buffer acumulado,
 * controle de aspas e limites do novo token.
 *
 * Campos chave:
 * - new_token: buffer temporário onde o token refinado é montado.
 * - idx / idx_new_token: índices do token original e do refinado.
 * - found_quote: indica se estamos dentro de uma aspa.
 * - last_start: coord. absoluta do início de um trecho agrupado.
 */
typedef struct s_refine_raw_token_params	t_refine_raw_token_vars;
struct s_refine_raw_token_params
{
	char	*new_token;
	int		idx_new_token;
	int		idx;
	int		found_quote;
	int		token_len;
	int		last_start;
};

/**
 * # t_refined_token_push_params
 *
 * Estrutura de escopo usada ao inserir tokens refinados na lista.
 * Carrega: token bruto, posição original, buffer parcial e o array
 * que receberá os novos chunks.
 *
 * É passada para funções especializadas de push.
 */
typedef struct s_refined_token_push_params	t_refined_token_push_params;
struct s_refined_token_push_params
{
	t_linkedlist_array		*refineds;
	int						idx_raw_token;
	int						new_token_start_idx;
	t_chunck				raw_token;
	t_refine_raw_token_vars	*var;
};

void				ft_refined_token_push(
						t_refined_token_push_params params);
void				ft_manage_grouped_and_ungrouped_tokens(
						t_refined_token_push_params scope);
t_chunck			*ft_create_chunck(
						char *token,
						int coord_start,
						int coord_end);
void				ft_refine_raw_token(
						t_chunck raw_token, int curr_idx,
						t_linkedlist_array *container);

#endif
