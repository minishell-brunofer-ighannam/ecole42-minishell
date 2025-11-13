/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:58:37 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/13 18:19:05 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_INTERNAL_H
# define TOKENIZE_INTERNAL_H

# include "libft.h"
# include "../../../linkedlist/linkedlist.h"
# include "../../lexer_utils/lexer_utils.h"

typedef struct s_token				t_token;

// ============================ FIND EXPANDABLE ============================
typedef struct s_expandable_section	t_expandable_section;
struct s_expandable_section
{
	t_linkedlist	*list;
	t_linkedlist	*coord_list;
	char			**array;
	int				**coord_array;
};
t_expandable_section	*ft_create_expandable_sections(void);
int						*ft_coord_dup(int *coord);
t_expandable_section	*ft_find_expandable(char *str);

// ============================ BUILD EXPANSION ============================
char					*ft_build_expansion(t_token *self);

#endif
