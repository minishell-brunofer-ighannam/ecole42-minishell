/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:17:49 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 17:02:15 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/core/executer/builtins/builtins.h"
#include "../../src/core/executer/env/env.h"
#include "../../src/core/parser/parser.h"
#include "../tests.h"

void	test1(t_linkedlist_array	*env);
void	test2(t_linkedlist_array	*env);
void	test3(t_linkedlist_array	*env);

int	main(int argc, char **argv, char **envp)
{
	t_linkedlist_array	*env;

	(void)argc;
	(void)argv;
	env = ft_init_ht_env(envp);
	test1(env);
	test2(env);
	test3(env);
	env->destroy(&env, ft_free_item_ht_env);
}

void	free_ast_node(void *arg)
{
	t_ast_node	*node;

	if (!arg)
		return ;
	node = (t_ast_node *)arg;
	node->destroy(&node, NULL);
}

void	test1(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 1;
	test.test_input = "echo hello|grep h";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_expander_callbacks callbacks = ft_create_expander_callbacks(ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_parser(test.test_input, callbacks, NULL, free_ast_node);
	if (ast)
	{
		ast->print(ast);
		ast->destroy(&ast, free_ast_node);
	}
}

void	test2(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 2;
	test.test_input = "echo hello| |grep h";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_expander_callbacks callbacks = ft_create_expander_callbacks(ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_parser(test.test_input, callbacks, NULL, free_ast_node);
	if (ast)
	{
		ast->print(ast);
		ast->destroy(&ast, free_ast_node);
	}
}

void	test3(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 3;
	test.test_input = "echo hello| &&grep h";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_expander_callbacks callbacks = ft_create_expander_callbacks(ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_parser(test.test_input, callbacks, NULL, free_ast_node);
	if (ast)
	{
		ast->print(ast);
		ast->destroy(&ast, free_ast_node);
	}
}
