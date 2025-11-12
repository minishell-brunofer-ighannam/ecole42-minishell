/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:36:19 by valero            #+#    #+#             */
/*   Updated: 2025/11/11 22:39:46 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

char	**ft_splitter(char const *str)
{
	char	**splitted;

	splitted = ft_refined_splitter(str);
	return (splitted);
}
