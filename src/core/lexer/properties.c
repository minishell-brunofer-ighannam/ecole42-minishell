/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:50:43 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 16:24:18 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

bool	ft_is_redirect_token(t_token *token)
{
	return (token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_HERE_DOC_IN
		|| token->type == TOKEN_APPEND_OUT);
}

bool	ft_is_logic_token(t_token *token)
{
	return (token->type == TOKEN_AND
		|| token->type == TOKEN_OR);
}

bool	ft_is_pipe_token(t_token *token)
{
	return (token->type == TOKEN_PIPE);
}

bool	ft_is_reserved_token(t_token *token)
{
	return (ft_is_redirect_token(token)
		|| ft_is_logic_token(token)
		|| ft_is_pipe_token(token));
}
