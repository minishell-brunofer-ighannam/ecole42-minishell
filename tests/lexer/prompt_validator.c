/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:14:30 by valero            #+#    #+#             */
/*   Updated: 2025/12/01 04:04:41 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/core/lexer/prompt_validator/prompt_validator.h"
#include "../../src/core/lexer/lexer_internal.h"
#include "../tests.h"

void	test_set1(void);
void	test_set2(void);

int	main(void)
{

	test_set1();
	test_set2();
	// printf("quotes: %d\n", verify_quotes("teste \"quotes closed\" \"haha\" \" "));
	// printf("parenthesis: %d\n", verify_parens("teste (\"quotes closed)\" \"haha\" \" "));
	// printf("promp1: %d\n", prompt_validator("teste (\"quotes closed)\" \"haha\" \" "));
	// printf("promp2: %d\n", prompt_validator("teste (\"quotes closed)\") \"haha\" \" "));
	// printf("promp3: %d\n", prompt_validator("echo \"hello world\""));                 // quotes fechadas
	// printf("promp4: %d\n", prompt_validator("echo \"hello world"));                   // quote aberta
	// printf("promp5: %d\n", prompt_validator("ls (echo test)"));                       // parênteses fechados
	// printf("promp6: %d\n", prompt_validator("ls (echo test"));                        // parêntese aberto
	// printf("promp7: %d\n", prompt_validator("echo `date`"));                          // backticks fechados
	// printf("promp8: %d\n", prompt_validator("echo `date"));                           // backtick aberto
	// printf("promp9: %d\n", prompt_validator("echo $(ls)"));                            // $() fechado
	// printf("promp10: %d\n", prompt_validator("echo $(ls"));                            // $() aberto
	// printf("promp11: %d\n", prompt_validator("echo $(echo $(date))"));                 // $() aninhado fechado
	// printf("promp12: %d\n", prompt_validator("echo $(echo $(date)"));                  // $() aninhado aberto
	// printf("promp13: %d\n", prompt_validator("echo \"$(date)\""));                     // quotes e $() fechados
	// printf("promp14: %d\n", prompt_validator("echo \"$(date)"));                       // quote aberta com $() fechado
	// printf("promp15: %d\n", prompt_validator("echo (echo $(ls) \"test\")"));           // parêntese com $() e quotes fechados
	// printf("promp16: %d\n", prompt_validator("echo (echo $(ls) \"test\")"));           // mesmo teste só para repetição
	// printf("promp17: %d\n", prompt_validator("echo (echo $(ls) \"test\""));            // parêntese aberto, quote aberta
	// printf("promp18: %d\n", prompt_validator("echo `echo $(date)`"));                  // backtick com $() aninhado fechado
	// printf("promp19: %d\n", prompt_validator("echo `echo $(date)`"));                  // repetição
	// printf("promp20: %d\n", prompt_validator("echo `echo $(date)`"));                  // repetição
}

void	print_result(void *arg)
{
	int	*result;

	result = (int *)arg;
	printf("%d", *result);
}

void	test_set1(void)
{
	int		result;
	char	*prompt;
	t_test	test;

	result = 0;
	test.teste_number = 1;
	prompt = "echo \"hello world\"";
	test.test_input = "echo \"hello world\"" " -> (quotes fechadas)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == -1;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 2;
	prompt = "echo \"hello world";
	test.test_input = "echo \"hello world" " -> (quote aberta)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == 5;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 3;
	prompt = "ls (echo test)";
	test.test_input = "ls (echo test)" " -> (parênteses fechados)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == -1;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 4;
	prompt = "ls (echo test";
	test.test_input = "ls (echo test" " -> (parêntese aberto)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == 3;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 5;
	prompt = "echo `date`";
	test.test_input = "echo `date`" " -> (backticks fechados)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == -1;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 6;
	prompt = "echo `date";
	test.test_input = "echo `date" " -> (backtick aberto)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == 5;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 7;
	prompt = "echo $(ls)";
	test.test_input = "echo $(ls)" " -> ($() fechado)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == -1;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 8;
	prompt = "echo $(ls";
	test.test_input = "echo $(ls" " -> ($() aberto)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == 6;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

}

void	test_set2(void)
{
	int		result;
	char	*prompt;
	t_test	test;

	result = 0;
	test.teste_number = 9;
	prompt = "echo $(echo $(date))";
	test.test_input = "echo $(echo $(date))" " -> ($() aninhado fechado)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == -1;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 10;
	prompt = "echo $(echo $(date)";
	test.test_input = "echo $(echo $(date)" " -> ($() aninhado aberto)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == 6;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 11;
	prompt = "echo \"$(date)\"";
	test.test_input = "echo \"$(date)\"" " -> (quotes e $() fechados)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == -1;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 12;
	prompt = "echo \"$(date)";
	test.test_input = "echo \"$(date)" " -> (quote aberta com $() fechado)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == 5;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 13;
	prompt = "echo (echo $(ls) \"test\")";
	test.test_input = "echo (echo $(ls) \"test\")" " -> (parêntese com $() e quotes fechados)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == -1;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 14;
	prompt = "echo (echo $(ls) \"test\"";
	test.test_input = "echo (echo $(ls) \"test\"" " -> (parêntese aberto, $() e quotes fechados)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == 5;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 15;
	prompt = "echo `echo $(date)`";
	test.test_input = "echo `echo $(date)`" " -> (backtick com $() aninhado fechado)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == -1;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 16;
	prompt = "echo (echo $(ls) \"test $(HOME\")";
	test.test_input = "echo (echo $(ls) \"test $(HOME\")" " -> (parêntese com $() aberto e quotes fechados)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == 24;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);

	test.teste_number = 17;
	prompt = "echo (echo $(ls) \"test)";
	test.test_input = "echo (echo $(ls) \"test)" " -> (parêntese com $() fechado e quote aberta)";
	result = ft_prompt_validator(prompt);
	test.test_ok = result == 17;
	print_test_and_result(test, print_result, &result);
	ft_print_structure_not_closed_error(prompt, result);
}
