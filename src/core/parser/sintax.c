/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 21:51:10 by valero            #+#    #+#             */
/*   Updated: 2025/11/25 22:15:45 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static bool	ft_is_redirect(t_token *node);

int	ft_get_precedence(t_token *node)
{
	int	max_precedence;

	max_precedence = 4;
	if (node->type == TOKEN_PAREN_OPEN)
		return (max_precedence - 0);
	if (ft_is_redirect(node))
		return (max_precedence - 1);
	if (node->type == TOKEN_PIPE)
		return (max_precedence - 2);
	if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		return (max_precedence - 3);
	return (0);
}

static bool	ft_is_redirect(t_token *node)
{
	if (node->type == TOKEN_REDIRECT_OUT
		|| node->type == TOKEN_REDIRECT_IN
		|| node->type == TOKEN_HERE_DOC_IN
		|| node->type == TOKEN_APPEND_OUT)
		return (true);
	return (false);
}
