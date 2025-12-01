/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:38:14 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 16:24:49 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_internal.h"

bool	ft_is_redirect_node(t_ast_node *node)
{
	return (node->type == AST_NODE_REDIRECT_OUT
		|| node->type == AST_NODE_REDIRECT_IN
		|| node->type == AST_NODE_HERE_DOC_IN
		|| node->type == AST_NODE_APPEND_OUT);
}

bool	ft_is_logic_node(t_ast_node *node)
{
	return (node->type == AST_NODE_AND
		|| node->type == AST_NODE_OR);
}

bool	ft_is_pipe_node(t_ast_node *node)
{
	return (node->type == AST_NODE_PIPE);
}

bool	ft_is_subshell_node(t_ast_node *node)
{
	return (node->type == AST_NODE_SUBSHELL);
}

bool	ft_is_reserved_node(t_ast_node *node)
{
	return (ft_is_redirect_node(node)
		|| ft_is_logic_node(node)
		|| ft_is_pipe_node(node));
}
