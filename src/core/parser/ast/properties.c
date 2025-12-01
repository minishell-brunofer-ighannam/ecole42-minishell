/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:38:14 by valero            #+#    #+#             */
/*   Updated: 2025/11/30 21:38:23 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_internal.h"

bool	ft_is_redirect_node(t_token *token)
{
	return (token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_HERE_DOC_IN
		|| token->type == TOKEN_APPEND_OUT);
}
