/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_quote_chuncks.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:52:40 by valero            #+#    #+#             */
/*   Updated: 2025/11/23 17:16:00 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATE_QUOTE_CHUNCKS_H
# define SEPARATE_QUOTE_CHUNCKS_H

# include "../../../../data_structures/data_structures.h"

/**
 * # t_token_section
 *
 * Representa um trecho isolado do token após a separação por aspas.
 * Guarda a substring crua, o tipo de aspa que a delimitou e
 * um callback de destruição.
 *
 * Uso:
 * - Identificar a natureza do trecho (sem aspas, "aspado", 'aspado')
 * - Permitir reconstrução e varredura sem perder informação estrutural.
 */
typedef struct s_token_section				t_token_section;
struct s_token_section
{
	char			*section;
	char			quote_type;
	void			*(*destroy)(t_token_section **self_ref);
};

/**
 * # t_token_separated_sections
 *
 * Container principal que armazena todas as seções separadas.
 * Mantém listas de seções e coordenadas, arrays equivalentes
 * e callbacks utilitários.
 *
 * Lógica:
 * - Coletar trechos unitários enquanto a string é varrida.
 * - Guardar coordenadas para reconstrução precisa.
 * - Converter listas em arrays para acesso rápido.
 * - Fornecer destruição segura e função para reconstruir
 *   a string sem aspas externas.
 */
typedef struct s_token_separated_sections	t_token_separated_sections;
struct s_token_separated_sections
{
	t_linkedlist	*list;
	t_linkedlist	*coord_list;
	t_token_section	**array;
	int				**coord_array;
	t_token_section	**(*copy_array)(t_token_separated_sections *self);
	int				**(*copy_coord_array)(void *arg);
	char			*(*to_noquotes_string)(t_token_separated_sections *self);
	void			*(*destroy)(t_token_separated_sections **self_ref);
};

t_token_separated_sections	*ft_separate_quote_chuncks(const char *str);

#endif
