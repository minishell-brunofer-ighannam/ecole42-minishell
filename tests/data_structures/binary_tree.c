/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 02:46:07 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 03:03:34 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
#include "../../src/data_structures/data_structures.h"

static void	test1(void);
static void	test2(void);
static void	test3(void);

int	main(void)
{
	test1();
	test2();
	test3();
}

static void	test1(void)
{
	t_test	test;

	test.teste_number = 1;
	test.test_input = "create binary_tree";
	t_binary_tree	*tree = ft_create_binary_tree();
	test.test_ok = tree->root == NULL;
	print_test(test);
	tree->destroy(&tree, NULL);
}

static void	test2(void)
{
	t_test	test;

	test.teste_number = 2;
	test.test_input = "add root node";
	t_binary_tree	*tree = ft_create_binary_tree();
	tree->push_content(tree, tree->root, true, ft_strdup("ola"));
	test.test_ok = !ft_strncmp(tree->root->content, "ola", 4);
	print_test(test);
	tree->destroy(&tree, free);
}

static void	test3(void)
{
	t_test	test;
	int		right_tests;

	test.teste_number = 3;
	test.test_input = "tree with depth = 3";
	right_tests = 0;
	t_binary_tree	*tree = ft_create_binary_tree();
	tree->push_content(tree, NULL, true, ft_strdup("root"));
	tree->push_content(tree, tree->root, true, ft_strdup("root.left"));
	tree->push_content(tree, tree->root, false, ft_strdup("root.right"));
	tree->push_content(tree, tree->root->right, true, ft_strdup("root.right.left"));
	tree->push_content(tree, tree->root->right->left, false, ft_strdup("root.right.left.right"));
	right_tests += !ft_strncmp(tree->root->content, "root", ft_strlen("root"));
	right_tests += !ft_strncmp(tree->root->left->content, "root.left", ft_strlen("root.left"));
	right_tests += !ft_strncmp(tree->root->right->content, "root.right", ft_strlen("root.right"));
	right_tests += !ft_strncmp(tree->root->right->left->content, "root.right.left", ft_strlen("root.right.left"));
	right_tests += !ft_strncmp(tree->root->right->left->right->content, "root.right.left.right", ft_strlen("root.right.left.right"));
	right_tests += tree->depth == 3;
	test.test_ok = right_tests == 6;
	print_test(test);
	tree->destroy(&tree, free);
}
