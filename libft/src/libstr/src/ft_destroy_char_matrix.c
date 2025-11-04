/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_char_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:37:14 by valero            #+#    #+#             */
/*   Updated: 2025/09/26 14:37:52 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

void	*ft_destroy_char_matrix(char ***char_matrix_ref)
{
	int	i;

	i = -1;
	while ((*char_matrix_ref)[++i])
	{
		free((*char_matrix_ref)[i]);
		(*char_matrix_ref)[i] = NULL;
	}
	free(*char_matrix_ref);
	*char_matrix_ref = NULL;
	return (NULL);
}
