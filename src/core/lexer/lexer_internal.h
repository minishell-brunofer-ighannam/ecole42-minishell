/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:57:15 by valero            #+#    #+#             */
/*   Updated: 2025/11/24 23:00:19 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H

# include "prompt_validator/prompt_validator.h"
# include "splitter/splitter.h"
# include <stdlib.h>

int		*ft_new_coord(int start, int end);
int		*ft_coord_dup(int *coord);
void	ft_print_structure_not_closed_error(const char *src, int error_idx);

#endif
