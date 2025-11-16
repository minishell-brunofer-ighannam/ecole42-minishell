/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable_object_internal.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:05:35 by valero            #+#    #+#             */
/*   Updated: 2025/11/16 15:03:01 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDABLE_OBJECT_INTERNAL_H
# define EXPANDABLE_OBJECT_INTERNAL_H

# include "libft.h"
# include "../../../../linkedlist/linkedlist.h"
# include "../../../lexer_utils/lexer_utils.h"
# include "../../tokenizer_internal.h"

typedef struct s_expandable_section	t_expandable_section;
struct s_expandable_section
{
	t_linkedlist	*list;
	t_linkedlist	*coord_list;
	char			**array;
	int				**coord_array;
	char			**(*copy_array)(t_expandable_section *self);
	int				**(*copy_coord_array)(t_expandable_section *self);
	void			*(*destroy)(t_expandable_section **self_ref);
};
t_expandable_section	*ft_create_expandable_sections(void);
t_expandable_section	*ft_find_expandable(const char *str);
t_expandable_section	*ft_find_keys_to_expand(
							t_expandable_section *expandable_sections);

#endif
