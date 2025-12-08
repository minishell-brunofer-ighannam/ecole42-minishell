/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_props.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:54:45 by ighannam          #+#    #+#             */
/*   Updated: 2025/12/08 15:59:26 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapper_internal.h"

t_token	**ft_get_tokens(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;

	ast_node = (t_ast_node *)(node->content);
	return (ast_node->tokens);
}

t_ast_node_type	ft_get_type(t_binary_tree_node *node)
{
	t_ast_node	*ast_node;

	ast_node = (t_ast_node *)(node->content);
	return (ast_node->type);
}
