/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:57:15 by valero            #+#    #+#             */
/*   Updated: 2025/11/16 22:55:16 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_INTERNAL_H
# define TOKENIZER_INTERNAL_H

# include "splitter/splitter.h"
# include <stdlib.h>

int	*ft_new_coord(int start, int end);
int	*ft_coord_dup(int *coord);

#endif
