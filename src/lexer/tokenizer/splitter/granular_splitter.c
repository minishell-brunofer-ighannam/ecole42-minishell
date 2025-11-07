/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   granular_splitter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:52:01 by valero            #+#    #+#             */
/*   Updated: 2025/11/07 12:31:25 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "splitter.h"

void	ft_granular_splitter(char const *str)
{
	char	**raw_split;

	t_linkedlist	***granular_split;

	raw_split = ft_raw_splitter(str);
	(void)raw_split;
}

// char **str = ["echo", 'texto', "|", ]
// echo teste|grep test>texte.txt
// ["( ) | ||", "", ""]
