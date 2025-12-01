/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:44:01 by valero            #+#    #+#             */
/*   Updated: 2025/11/28 18:21:44 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/core/executer/builtins/builtins.h"
#include "../../src/core/executer/env/env.h"
#include "../../src/core/lexer/lexer.h"
#include "../../src/core/parser/parser_internal.h"
#include "../tests.h"
#include "../../includes/minishell.h"

static void	test1(t_linkedlist_array	*env);
static void	test2(t_linkedlist_array	*env);
static void	test3(t_linkedlist_array	*env);
static void	test4(t_linkedlist_array	*env);

int	main(int argc, char **argv, char **envp)
{
	t_linkedlist_array	*env;

	(void)argc;
	(void)argv;
	env = ft_init_ht_env(envp);
	test1(env);
	test2(env);
	test3(env);
	test4(env);
	env->destroy(&env, ft_free_item_ht_env);
}

static void	test1(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 1;
	test.test_input = "echo hello|grep -E \"[regex]\">outfile.txt&&(echo subshell)";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
}

static void	test2(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 2;
	test.test_input = "ls -l |grep expand &&  wc -l || (echo \"olá\" > file) ";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
}

// > f1 > f2 >f3 echo ola

static void	test3(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 3;
	test.test_input = "> f1 > f2 >f3 echo ola";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
}

static void	test4(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 4;
	test.test_input = "echo > f1 > f2 >f3 ola";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
}
