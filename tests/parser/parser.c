/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:17:49 by valero            #+#    #+#             */
/*   Updated: 2025/12/03 18:11:00 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/core/executer/builtins/builtins.h"
#include "../../src/core/executer/env/env.h"
#include "../../src/core/executer/executer.h"
#include "../../src/core/parser/parser.h"
#include "../tests.h"

void	test1(t_linkedlist_array	*env);
void	test2(t_linkedlist_array	*env);
void	test3(t_linkedlist_array	*env);
void	test4(t_linkedlist_array	*env);
void	test5(t_linkedlist_array	*env);
void	test6(t_linkedlist_array	*env);
void	test7(t_linkedlist_array	*env);
void	test8(t_linkedlist_array	*env);
void	test9(t_linkedlist_array	*env);
void	test10(t_linkedlist_array	*env);
void	test11(t_linkedlist_array	*env);
void	test12(t_linkedlist_array	*env);
void	test13(t_linkedlist_array	*env);
void	test14(t_linkedlist_array	*env);
void	test15(t_linkedlist_array	*env);
void	test16(t_linkedlist_array	*env);
void	test17(t_linkedlist_array	*env);
void	test18(t_linkedlist_array	*env);
void	test19(t_linkedlist_array	*env);
void	test20(t_linkedlist_array	*env);
void	test21(t_linkedlist_array	*env);
void	test22(t_linkedlist_array	*env);
void	test23(t_linkedlist_array	*env);
void	test24(t_linkedlist_array	*env);
void	test25(t_linkedlist_array	*env);
void	test26(t_linkedlist_array	*env);
void	test27(t_linkedlist_array	*env);
void	test28(t_linkedlist_array	*env);
void	test29(t_linkedlist_array	*env);
void	test30(t_linkedlist_array	*env);
void	test31(t_linkedlist_array	*env);
void	test32(t_linkedlist_array	*env);
void	test33(t_linkedlist_array	*env);
void	test34(t_linkedlist_array	*env);
void	test35(t_linkedlist_array	*env);
void	test36(t_linkedlist_array	*env);
void	test37(t_linkedlist_array	*env);
void	test38(t_linkedlist_array	*env);
void	test39(t_linkedlist_array	*env);
void	test40(t_linkedlist_array	*env);
void	test41(t_linkedlist_array	*env);
void	test42(t_linkedlist_array	*env);
void	test43(t_linkedlist_array	*env);
void	test44(t_linkedlist_array	*env);
void	test45(t_linkedlist_array	*env);
void	test46(t_linkedlist_array	*env);
void	test47(t_linkedlist_array	*env);
void	test48(t_linkedlist_array	*env);
void	test49(t_linkedlist_array	*env);
void	test50(t_linkedlist_array	*env);
void	test51(t_linkedlist_array	*env);
void	test52(t_linkedlist_array	*env);
void	test53(t_linkedlist_array	*env);
void	test54(t_linkedlist_array	*env);
void	test55(t_linkedlist_array	*env);
void	test56(t_linkedlist_array	*env);
void	test57(t_linkedlist_array	*env);
void	test58(t_linkedlist_array	*env);
void	test59(t_linkedlist_array	*env);
void	test60(t_linkedlist_array	*env);
void	test61(t_linkedlist_array	*env);
void	test62(t_linkedlist_array	*env);
void	test63(t_linkedlist_array	*env);
void	test64(t_linkedlist_array	*env);

int	main(int argc, char **argv, char **envp)
{
	t_linkedlist_array	*env;

	(void)argc;
	(void)argv;
	env = ft_init_ht_env(envp);
	ft_putstr_fd("\n\n--------------- Testes Iniciais ---------------\n", 1);
	test1(env);
	test2(env);
	ft_putstr_fd("\n\n--------------- Testes com Pipes ---------------\n", 1);
	test3(env);
	test4(env);
	test5(env);
	test6(env);
	ft_putstr_fd("\n\n--------------- Testes com Condicionais ---------------\n", 1);
	test7(env);
	test8(env);
	test9(env);
	test10(env);
	test11(env);
	ft_putstr_fd("\n\n--------------- Condicionais misturados com Pipes ---------------\n", 1);
	test12(env);
	test13(env);
	test14(env);
	test15(env);
	ft_putstr_fd("\n\n--------------- Redirecionamentos simples ---------------\n", 1);
	test16(env);
	test17(env);
	test18(env);
	test19(env);
	ft_putstr_fd("\n\n--------------- Redirecionamentos múltiplos ---------------\n", 1);
	test20(env);
	test21(env);
	test22(env);
	ft_putstr_fd("\n\n--------------- Redirecionamentos + Pipes ---------------\n", 1);
	test23(env);
	test24(env);
	test25(env);
	test26(env);
	ft_putstr_fd("\n\n--------------- Heredoc (<<) ---------------\n", 1);
	test27(env);
	test28(env);
	test29(env);
	test30(env);
	ft_putstr_fd("\n\n--------------- Subshells ---------------\n", 1);
	test31(env);
	test32(env);
	test33(env);
	test34(env);
	test35(env);
	test36(env);
	test37(env);
	test38(env);
	test39(env);
	ft_putstr_fd("\n\n--------------- Subshells + Condicionais + Pipes ---------------\n", 1);
	test40(env);
	test41(env);
	test42(env);
	test43(env);
	test44(env);
	ft_putstr_fd("\n\n--------------- Subshells + Redirecionamentos ---------------\n", 1);
	test45(env);
	test46(env);
	test47(env);
	test48(env);
	ft_putstr_fd("\n\n--------------- Testes realmente cruéis — mistura máxima ---------------\n", 1);
	test49(env);
	test50(env);
	test51(env);
	test52(env);
	test53(env);
	test54(env);
	ft_putstr_fd("\n\n--------------- Casos de erro proposital ---------------\n", 1);
	test55(env);
	test56(env);
	test57(env);
	test58(env);
	test59(env);
	test60(env);
	test61(env);
	test62(env);
	test63(env);
	test64(env);
	env->destroy(&env, ft_free_item_ht_env);
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

/*

	ISADORA -> FIQUE ATENTA NESSES TESTEST

 */

void	test3(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 3;
	test.test_input = "echo ok | cat | grep o";
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

void	test4(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 4;
	test.test_input = "echo a | (cat | grep a)";
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

void	test5(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 5;
	test.test_input = "(echo 1 | echo 2)";
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

void	test6(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 6;
	test.test_input = "echo \"x\" | | cat";
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

void	test7(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 7;
	test.test_input = "true && echo yes";
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

void	test8(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 8;
	test.test_input = "false || echo fallback";
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

void	test9(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 9;
	test.test_input = "false && echo no || echo yes";
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

void	test10(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 10;
	test.test_input = "echo a && echo b || echo c";
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

void	test11(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 11;
	test.test_input = "(false && echo X) || (echo Y && echo Z)";
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

void	test12(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 12;
	test.test_input = "echo a | grep a && echo passou";
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

void	test13(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 13;
	test.test_input = "echo a | grep b || echo falhou";
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

void	test14(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 14;
	test.test_input = "( echo a | grep a ) && ( echo b | grep b )";
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

void	test15(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 15;
	test.test_input = "( echo a | grep x ) || ( echo y | grep y )";
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

void	test16(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 16;
	test.test_input = "echo hello > file1";
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

void	test17(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 17;
	test.test_input = "cat < file1";
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

void	test18(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 18;
	test.test_input = "echo test >> file1";
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

void	test19(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 19;
	test.test_input = "cat < nonexistent";
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

void	test20(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 20;
	test.test_input = "echo A > a > b";
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

void	test21(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 21;
	test.test_input = "echo B >> a >> b";
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

void	test22(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 22;
	test.test_input = "cat < a < b";
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

void	test23(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 23;
	test.test_input = "cat < file | grep x";
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

void	test24(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 24;
	test.test_input = "echo ok | tee out.txt > log";
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

void	test25(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 25;
	test.test_input = "echo 123 | cat > out.txt";
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

void	test26(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 26;
	test.test_input = "ls | grep txt > resultado";
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

void	test27(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 27;
	test.test_input = "cat << EOF";
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

void	test28(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 28;
	test.test_input = "cat <<EOF | grep linha";
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

void	test29(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 29;
	test.test_input = "cat << \"EOF\"";
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

void	test30(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 30;
	test.test_input = "false || cat <<END";
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

void	test31(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 31;
	test.test_input = "(echo dentro)";
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

void	test32(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 32;
	test.test_input = "(echo a && echo b)";
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

void	test33(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 33;
	test.test_input = "(echo a | grep a)";
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

void	test34(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 34;
	test.test_input = "( (echo a) )";
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

void	test35(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 35;
	test.test_input = "( (echo x) && (echo y) )";
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

void	test36(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 36;
	test.test_input = "()";
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

void	test37(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 37;
	test.test_input = "(   )";
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

void	test38(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 38;
	test.test_input = "( echo a";
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

void	test39(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 39;
	test.test_input = "echo a ) )";
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

void	test40(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 40;
	test.test_input = "( echo a && echo b ) | grep a";
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

void	test41(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 41;
	test.test_input = "( echo a | grep a ) && echo ok";
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

void	test42(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 42;
	test.test_input = "( false || echo fallback ) && echo ok";
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

void	test43(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 43;
	test.test_input = "( echo a && false ) || echo caiu";
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

void	test44(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 44;
	test.test_input = "( (echo a) | (grep a) ) && echo ok";
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

void	test45(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 45;
	test.test_input = "( echo a ) > out";
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

void	test46(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 46;
	test.test_input = "( echo a > out1 ) && cat out1";
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

void	test47(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 47;
	test.test_input = "( cat < in ) | grep x";
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

void	test48(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 48;
	test.test_input = "( cat <<EOF)";
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

void	test49(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 49;
	test.test_input = "( echo a && echo b ) | ( grep a && cat ) > out";
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

void	test50(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 50;
	test.test_input = "( (echo 1 | grep 1) && (echo 2 | grep 2) ) || echo falha";
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

void	test51(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 51;
	test.test_input = "( false && echo x ) || ( echo ok | tee log ) >> out";
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

void	test52(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 52;
	test.test_input = "echo inicio && ( echo meio | grep m ) && echo fim";
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

void	test53(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 53;
	test.test_input = "( cat < in || echo sem_in ) | grep algo > log";
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

void	test54(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 54;
	test.test_input = "((echo x)|| (echo y && echo z)) | cat >> final";
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

void	test55(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 55;
	test.test_input = "| echo x";
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

void	test56(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 56;
	test.test_input = "echo x ||";
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

void	test57(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 57;
	test.test_input = "&& echo y";
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

void	test58(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 58;
	test.test_input = "echo x >";
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

void	test59(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 59;
	test.test_input = "echo x >>";
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

void	test60(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 60;
	test.test_input = "cat <";
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

void	test61(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 61;
	test.test_input = "(cat < )";
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

void	test62(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 62;
	test.test_input = "( echo x > )";
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

void	test63(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 63;
	test.test_input = "( | echo x )";
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

void	test64(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 64;
	test.test_input = "echo x >>> out";
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
