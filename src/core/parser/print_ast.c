/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 00:24:55 by valero            #+#    #+#             */
/*   Updated: 2025/11/27 02:26:40 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static void	ft_print_ast_node(t_binary_tree_node *node, int depth, char *prefix, int is_last_child);

void	ft_print_ast(t_ast *self)
{
    if (!self || !self->tree || !self->tree->root)
        return ;

    // Inicia a impressão da árvore a partir da raiz
    ft_print_ast_node(self->tree->root, 0, "", 1);
}

static void	ft_print_ast_node(t_binary_tree_node *node, int depth, char *prefix, int is_last_child)
{
	t_ast_node	*content;
	int			i;
	char		new_prefix[256];
	int			j;

	if (!node || !node->content)
		return ;
	ft_bzero(new_prefix, 256 * sizeof(char));
	if (depth > 0)
		ft_putstr_fd(prefix + 4, 1);
	if (depth > 0)
	{
		if (is_last_child)
			ft_putstr_fd("└── ", 1);
		else
			ft_putstr_fd("├── ", 1);
	}
	content = (t_ast_node *)node->content;
	ft_putstr_fd("(", 1);
	if (content->type == AST_NODE_SUBSHELL)
		ft_putstr_fd("SUB", 1);
	else
	{
		i = -1;
		while (content->tokens[++i])
		{
			ft_putstr_fd((char *)content->tokens[i]->value, 1);
			if (content->tokens[i + 1])
				ft_putstr_fd(" ", 1);
		}
	}
	ft_putstr_fd(")", 1);
	ft_putstr_fd("\n", 1);
	j = -1;
	while (prefix[++j] && j < 255)
		new_prefix[j] = prefix[j];
	if (is_last_child)
	{
		new_prefix[j++] = ' ';
		new_prefix[j++] = ' ';
		new_prefix[j++] = ' ';
		new_prefix[j++] = ' ';
	}
	else
	{
		new_prefix[j++] = '\xe2';
		new_prefix[j++] = '\x94';
		new_prefix[j++] = '\x82';
		new_prefix[j++] = ' ';
		new_prefix[j++] = ' ';
		new_prefix[j++] = ' ';
	}
	if (node->left)
		ft_print_ast_node(node->left, depth + 1, new_prefix, node->right == NULL);
	if (node->right)
		ft_print_ast_node(node->right, depth + 1, new_prefix, 1);
}
