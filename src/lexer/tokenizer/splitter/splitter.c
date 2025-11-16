/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:36:19 by valero            #+#    #+#             */
/*   Updated: 2025/11/16 15:28:44 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter_internal.h"

t_splited_prompt	*ft_splitter(char const *str)
{
	t_splited_prompt	*splitted;

	splitted = ft_refined_splitter(str);
	return (splitted);
}
