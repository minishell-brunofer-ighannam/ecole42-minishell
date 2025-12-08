/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:58:37 by brunofer          #+#    #+#             */
/*   Updated: 2025/12/08 15:27:05 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_INTERNAL_H
# define TOKENIZE_INTERNAL_H

# include "libft.h"
# include "../../../data_structures/data_structures.h"
# include "../../../utils/utils.h"
# include "./expandable_object/expandable_object.h"
# include "../lexer_internal.h"
# include "separate_quote_chuncks/separate_quote_chuncks.h"
# include "tokenize.h"

// ============================ BUILD EXPANSION ============================
int						ft_create_expanded_value(t_token *token);
void					ft_merge_expansion(t_token *token);
char					*ft_normilize_char_matrix(char **matrix);
t_expansion_build		*ft_build_expansion_result(
							t_token *token, char *glob_input);
t_expansion_build		*ft_expansion_build_dup(t_expansion_build *last_build);
t_expansion_build		*ft_build_expansion(
							t_token *token, t_linkedlist_array *ht_env);
t_token					*ft_create_token(const char *value, int position,
							int *coord_in_src,
							t_expander_callbacks callbacks);

#endif
