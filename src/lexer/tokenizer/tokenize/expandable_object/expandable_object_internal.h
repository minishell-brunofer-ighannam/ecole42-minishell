/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable_object_internal.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:05:35 by valero            #+#    #+#             */
/*   Updated: 2025/11/22 15:10:04 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDABLE_OBJECT_INTERNAL_H
# define EXPANDABLE_OBJECT_INTERNAL_H

# include "libft.h"
# include "../../../../data_structures/data_structures.h"
# include "../../../lexer_utils/lexer_utils.h"
# include "../../tokenizer_internal.h"
# include "../separate_quote_chuncks/separate_quote_chuncks.h"

/**
 * # t_expandable_section
 *
 * Estrutura intermediária usada para coletar seções do token
 * que podem conter expansões (`$VAR`, `$1`, `$?`, etc.).
 *
 * Armazena:
 * - `list`: lista encadeada com as seções de texto.
 * - `coord_list`: mesmas seções, mas guardando {start, end}.
 * - `array` / `coord_array`: versões lineares das listas.
 *
 * Finalidade:
 * Servir como “buffer de descoberta”. Tudo que pode ser expandido
 * passa por aqui antes de ser filtrado e montado no objeto final.
 */
typedef struct s_expandable_section			t_expandable_section;
struct s_expandable_section
{
	t_linkedlist	*list;
	t_linkedlist	*coord_list;
	char			**array;
	int				**coord_array;
	char			**(*copy_array)(t_expandable_section *self);
	int				**(*copy_coord_array)(void *arg);
	void			*(*destroy)(t_expandable_section **self_ref);
};
t_expandable_section		*ft_create_expandable_sections(void);
int							**ft_copy_coord_matrix(void *arg);
t_expandable_section		*ft_find_expandable(const char *str);
t_expandable_section		*ft_find_keys_to_expand(
								t_expandable_section *expandable_sections);

#endif
