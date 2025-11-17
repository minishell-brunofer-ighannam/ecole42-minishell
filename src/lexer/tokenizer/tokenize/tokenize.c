/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:59:37 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/16 22:25:08 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize_internal.h"

t_token	*ft_tokenize(
			const char *chunck,
			int idx,
			int *coord_in_src,
			t_expander_callbacks callbacks)
{
	t_token	*token;

	token = ft_create_token(chunck, idx, coord_in_src, callbacks);
	if (!token)
		return (NULL);
	return (token);
}
