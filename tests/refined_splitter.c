/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:13:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 20:47:22 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

static void	print_result(void *arg);
static void	test1(void);
static void	test2(void);
static void	test3(void);
static void	test4(void);
static void	test5(void);
// static void	test6(void);
static void	test7(void);
static void	test8(void);
static void	test9(void);
static void	test10(void);

int	main(int argc, char **argv)
{
	char	**splitted_argv;
	int		i;

	splitted_argv = NULL;
	if (argc >= 2)
	{
		splitted_argv = ft_refined_splitter(argv[1]);
		i = -1;
		while (splitted_argv[++i])
			printf("[%s] ", splitted_argv[i]);
		printf("\n");
		ft_destroy_char_matrix(&splitted_argv);
	}
	test1();
	test2();
	test3();
	test4();
	test5();
	// (void)test6;
	test7();
	test8();
	test9();
	test10();
}

static void	print_result(void *arg)
{
	int		i;
	char	**splitted;

	splitted = (char **)arg;
	i = -1;
	while (splitted[++i])
		printf("[%s] ", splitted[i]);
}

static void	test1(void)
{
	t_test	test;
	char	**splitted;
	int		i;
	int		right_tokens;

	test.teste_number = 2;
	test.test_input = "echo \"hello Bruno \" | grep br";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\"hello Bruno \"", "|", "grep", "br", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (!ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted);
	ft_destroy_char_matrix(&splitted);
}

static void	test2(void)
{
	t_test	test;
	char	**splitted;
	int		i;
	int		right_tokens;

	test.teste_number = 2;
	test.test_input = "echo \"ola eu sou o 'bruno'    \" && echo ' teste 2 ' > \"$HOME\" && echo \"Moro em \\\" Jd. Real \\\"\"";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\"ola eu sou o 'bruno'    \"", "&&", "echo", "' teste 2 '", ">", "\"$HOME\"", "&&", "echo", "\"Moro em \\\" Jd. Real \\\"\"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted);
	ft_destroy_char_matrix(&splitted);
}

static void	test3(void)
{
	t_test	test;
	char	**splitted;
	int		i;
	int		right_tokens;

	test.teste_number = 3;
	test.test_input = "echo \" teste dois\"|\"grudado\" |grep \" ola meu chapa \" ";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\" teste dois\"", "|", "\"grudado\"", "|", "grep", "\" ola meu chapa \"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted);
	ft_destroy_char_matrix(&splitted);
}

static void	test4(void)
{
	t_test	test;
	char	**splitted;
	int		i;
	int		right_tokens;

	test.teste_number = 4;
	test.test_input = "echo \" teste dois\"\"grudado\" |grep \" ola meu chapa \" ";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\" teste doisgrudado\"", "|", "grep", "\" ola meu chapa \"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted);
	ft_destroy_char_matrix(&splitted);
}

static void	test5(void)
{
	t_test	test;
	char	**splitted;
	int		i;
	int		right_tokens;

	test.teste_number = 5;
	test.test_input = "echo \" teste dois\"\"\"\"grudado\" |grep \" ola meu chapa \" ";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\" teste doisgrudado\"", "|", "grep", "\" ola meu chapa \"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted);
	ft_destroy_char_matrix(&splitted);
}

// static void	test6(void)
// {
// 	t_test	test;
// 	char	**splitted;
// 	int		i;
// 	int		right_tokens;

// 	test.teste_number = 6;
// 	test.test_input = "echo 'it'\\''s fine' \" and \\\"ok\\\"\" ; ls -l";
// 	splitted = ft_refined_splitter(test.test_input);
// 	char	*expected[] = {"echo", "'it'\\''s fine'", "\" and \\\"ok\\\"\"", ";", "ls", "-l", NULL};
// 	right_tokens = 0;
// 	i = 0;
// 	while (expected[i])
// 	{
// 		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
// 			right_tokens++;
// 		i++;
// 	}
// 	test.test_ok = i == right_tokens;
// 	print_test_and_result(test, print_result, splitted);
// 	ft_destroy_char_matrix(&splitted);
// }

static void	test7(void)
{
	t_test	test;
	char	**splitted;
	int		i;
	int		right_tokens;

	test.teste_number = 7;
	test.test_input = "FOO=\"foo bar\"; echo $FOO \"$FOO\"";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"FOO=\"foo bar\"", ";", "echo", "$FOO", "\"$FOO\"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted);
	ft_destroy_char_matrix(&splitted);
}

static void	test8(void)
{
	t_test	test;
	char	**splitted;
	int		i;
	int		right_tokens;

	test.teste_number = 8;
	test.test_input = "echo \"today is $(date +\"%Y-%m-%d\")\" && printf 'ok\\n'";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\"today is $(date +\"%Y-%m-%d\")\"", "&&", "printf", "'ok\\n'", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted);
	ft_destroy_char_matrix(&splitted);
}

static void	test9(void)
{
	t_test	test;
	char	**splitted;
	int		i;
	int		right_tokens;

	test.teste_number = 9;
	test.test_input = "out=`echo foo $(echo \"bar baz\")` ; echo \"$out\"";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"out=", "`", "echo foo ", "$(", "echo \"bar baz\"", ")", "`", ";", "echo", "\"$out\"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted);
	ft_destroy_char_matrix(&splitted);
}

static void	test10(void)
{
	t_test	test;
	char	**splitted;
	int		i;
	int		right_tokens;

	test.teste_number = 10;
	test.test_input = "command 2>&1 > file.txt 1>>log.txt";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"command", "2", ">&", "1", ">", "file.txt", "1", ">>", "log.txt", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted);
	ft_destroy_char_matrix(&splitted);
}


