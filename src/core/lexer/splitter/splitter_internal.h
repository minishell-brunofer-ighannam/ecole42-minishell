/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 23:38:47 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 22:29:11 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLITTER_INTERNAL_H
# define SPLITTER_INTERNAL_H

# include "../../../data_structures/data_structures.h"
# include "../../../utils/utils.h"
# include "refined_splitter/refined_splitter.h"
# include "splitter.h"
# include <stdbool.h>

typedef struct s_chunck						t_chunck;
struct s_chunck
{
	char	*chunck;
	int		*coord;
	void	*(*destroy)(t_chunck **self_ref);
};

t_splited_prompt	*ft_create_splited_prompt(void);
bool				ft_is_quote(const char *str, int idx, char *other_symbols);
t_splited_prompt	*ft_raw_splitter(char const *str);

#endif
