/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 00:24:55 by valero            #+#    #+#             */
/*   Updated: 2025/12/08 13:14:39 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_internal.h"

static void	ft_print_ast_node(
				t_binary_tree_node *node, int depth,
				char *prefix, int is_last_child);
static void	ft_add_space(char new_prefix[256], int *prefix_idx);
static void	ft_add_column(char new_prefix[256], int *prefix_idx);
static void	ft_print_content(
				t_ast_node	*content, int depth,
				char *prefix, int is_last_child);

void	ft_print_ast(t_ast *self)
{
	if (!self || !self->tree || !self->tree->root)
		return ;
	ft_print_ast_node(self->tree->root, 0, "", 1);
}

static void	ft_print_ast_node(
				t_binary_tree_node *node, int depth,
				char *prefix, int is_last_child)
{
	t_ast_node	*content;
	char		new_prefix[256];
	int			prefix_idx;

	if (!node || !node->content)
		return ;
	ft_bzero(new_prefix, 256 * sizeof(char));
	content = (t_ast_node *)node->content;
	ft_print_content(content, depth, prefix, is_last_child);
	prefix_idx = -1;
	while (prefix[++prefix_idx] && prefix_idx < 255)
		new_prefix[prefix_idx] = prefix[prefix_idx];
	if (is_last_child)
		ft_add_space(new_prefix, &prefix_idx);
	else
		ft_add_column(new_prefix, &prefix_idx);
	if (node->left)
		ft_print_ast_node(node->left, depth + 1,
			new_prefix, node->right == NULL);
	if (node->right)
		ft_print_ast_node(node->right, depth + 1, new_prefix, 1);
}

static void	ft_add_space(char new_prefix[256], int *prefix_idx)
{
	new_prefix[(*prefix_idx)++] = ' ';
	new_prefix[(*prefix_idx)++] = ' ';
	new_prefix[(*prefix_idx)++] = ' ';
	new_prefix[(*prefix_idx)++] = ' ';
}

static void	ft_add_column(char new_prefix[256], int *prefix_idx)
{
	new_prefix[(*prefix_idx)++] = '\xe2';
	new_prefix[(*prefix_idx)++] = '\x94';
	new_prefix[(*prefix_idx)++] = '\x82';
	new_prefix[(*prefix_idx)++] = ' ';
	new_prefix[(*prefix_idx)++] = ' ';
	new_prefix[(*prefix_idx)++] = ' ';
}

static void	ft_print_content(
				t_ast_node	*content, int depth,
				char *prefix, int is_last_child)
{
	int			i;

	if (depth > 0)
	{
		ft_putstr_fd(prefix + 4, 1);
		if (is_last_child)
			ft_putstr_fd("└── ", 1);
		else
			ft_putstr_fd("├── ", 1);
	}
	ft_putstr_fd("(", 1);
	if ((content)->type == AST_NODE_SUBSHELL)
		ft_putstr_fd("SUB", 1);
	else
	{
		i = -1;
		while ((content)->tokens[++i])
		{
			ft_putstr_fd((char *)(content)->tokens[i]->value, 1);
			if ((content)->tokens[i + 1])
				ft_putstr_fd(" ", 1);
		}
	}
	ft_putstr_fd(")", 1);
	ft_putstr_fd("\n", 1);
}
