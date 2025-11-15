/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:58:37 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/14 20:26:00 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_INTERNAL_H
# define TOKENIZE_INTERNAL_H

# include "libft.h"
# include "../../../linkedlist/linkedlist.h"
# include "../../lexer_utils/lexer_utils.h"
# include "./expandable_object/expandable_object.h"
# include "tokenize.h"

// ============================ BUILD EXPANSION ============================
char					*ft_build_expansion(t_token *self);
t_token					*ft_create_token(const char *value, int position,
							int coord_in_src[2],
							t_expander_callbacks callbacks);

#endif
