/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:44:01 by valero            #+#    #+#             */
/*   Updated: 2025/12/03 19:52:16 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/core/executer/builtins/builtins.h"
#include "../../src/core/executer/env/env.h"
#include "../../src/core/lexer/lexer.h"
#include "../../src/core/executer/executer.h"
#include "../../src/core/parser/ast_build/ast_build_internal.h"
#include "../tests.h"
#include "../../includes/minishell.h"

void	test1(t_linkedlist_array	*env);
void	test2(t_linkedlist_array	*env);
void	test3(t_linkedlist_array	*env);
void	test4(t_linkedlist_array	*env);
void	test5(t_linkedlist_array	*env);
void	test6(t_linkedlist_array	*env);
void	test7(t_linkedlist_array	*env);

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
	test5(env);
	test6(env);
	test7(env);
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
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
	ast->destroy(&ast, free_ast_node);
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
	test.test_input = "echo hello|grep -E \"[regex]\">outfile.txt&&(echo subshell)";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
	ast->destroy(&ast, free_ast_node);
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
	test.test_input = "ls -l |grep expand &&  wc -l || (echo \"olá\" > file) ";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
	ast->destroy(&ast, free_ast_node);
}

// > f1 > f2 >f3 echo ola

void	test4(t_linkedlist_array	*env)
{
	t_test	test;

	ft_export(env, "USER=lexer");
	ft_export(env, "PLACE=42");
	ft_export(env, "TOWN=SaoPaulo");
	ft_export(env, "STATE=SP");
	ft_export(env, "COUNTRY=BR");
	test.teste_number = 4;
	test.test_input = "> f1 > f2 >f3 echo ola";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
	ast->destroy(&ast, free_ast_node);
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
	test.test_input = "echo > f1 > f2 >f3 ola";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
	ast->destroy(&ast, free_ast_node);
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
	test.test_input = "(echo > f1|grep oi&&(echo tambem))";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
	ast->destroy(&ast, free_ast_node);
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
	test.test_input = "( cd /home/user && ( ls -l | grep \"log\" || echo \"No logs found\" ) > logs.txt ) && ( (echo \"Process started\" && (date && echo \"Working...\" > temp.txt) ) || (echo \"Process failed\" && tail -n 10 /var/log/syslog >> error.log ) ) && ( cat logs.txt | grep -v \"error\" | tee cleaned_logs.txt > /dev/null ) || ( (echo \"Cleanup started\" && rm -rf /tmp/* && echo \"Temp files removed\" ) && echo \"Backup started\" && cp -r /home/user /backup/ && echo \"Backup completed\" ) && ( ( (echo \"Final step\" && ls /home/user ) > result.log ) || ( echo \"Final step failed\" >> result.log ) )";
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(PRINT_BOLD PRINT_LIGHT_BLUE, 1);
	ft_putstr_fd(test.test_input, 1);
	ft_putstr_fd(PRINT_RESET, 1);
	ft_putstr_fd("\n", 1);
	t_lexer *lexer = ft_lexer(test.test_input, ft_expand_var, ft_expand_glob);
	t_ast	*ast = ft_ast_build(lexer, NULL);
	ast->print(ast);
	ast->destroy(&ast, free_ast_node);
}

// ( cd /home/user && ( ls -l | grep "log" || echo "No logs found" ) > logs.txt ) && ( (echo "Process started" && (date && echo "Working..." > temp.txt) ) || (echo "Process failed" && tail -n 10 /var/log/syslog >> error.log ) ) && ( cat logs.txt | grep -v "error" | tee cleaned_logs.txt > /dev/null ) || ( (echo "Cleanup started" && rm -rf /tmp/* && echo "Temp files removed" ) && echo "Backup started" && cp -r /home/user /backup/ && echo "Backup completed" ) && ( ( (echo "Final step" && ls /home/user ) > result.log ) || ( echo "Final step failed" >> result.log ) )

