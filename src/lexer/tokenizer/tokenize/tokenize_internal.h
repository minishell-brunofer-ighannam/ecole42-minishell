/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:58:37 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/17 02:02:25 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_INTERNAL_H
# define TOKENIZE_INTERNAL_H

# include "libft.h"
# include "../../../linkedlist/linkedlist.h"
# include "../../../linkedlist_array/linkedlist_array.h"
# include "../../lexer_utils/lexer_utils.h"
# include "./expandable_object/expandable_object.h"
# include "../tokenizer_internal.h"
# include "tokenize.h"

// ============================ BUILD EXPANSION ============================
char					*ft_normilize_char_matrix(char **matrix);
t_expansion_build		*ft_build_expansion_result(
							t_token *token, char *glob_input);
t_expansion_build		*ft_expansion_build_dup(t_expansion_build *last_build);
t_expansion_build		*ft_build_expansion(t_token *token, t_linkedlist_array *ht_env);
t_token					*ft_create_token(const char *value, int position,
							int *coord_in_src,
							t_expander_callbacks callbacks);

#endif
