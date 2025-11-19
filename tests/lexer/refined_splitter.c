/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:13:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/19 13:06:19 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/lexer/tokenizer/splitter/splitter_internal.h"
#include "../tests.h"

static void	print_result(void *arg);
static void	test1(void);
static void	test2(void);
static void	test3(void);
static void	test4(void);
static void	test5(void);
static void	test6(void);
static void	test7(void);
static void	test8(void);
static void	test9(void);
static void	test10(void);
static void	test11(void);
static void	test12(void);
static void	test13(void);
static void	test14(void);

int	main(int argc, char **argv)
{
	t_splited_prompt *splitted_argv;
	int		i;

	splitted_argv = NULL;
	if (argc >= 2)
	{
		splitted_argv = ft_refined_splitter(argv[1]);
		i = -1;
		while (splitted_argv->chuncks[++i])
			printf("[%s] ", splitted_argv->chuncks[i]);
		printf("\n");
		splitted_argv->destroy(&splitted_argv);
	}
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();
	test12();
	test13();
	test14();
}

static void	print_result(void *arg)
{
	int		i;
	char	**result;

	result = (char **)arg;
	i = -1;
	while (result[++i])
		printf("[%s] ", result[i]);
}

static void	test1(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 1;
	test.test_input = "echo \"hello Bruno \" | grep br";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\"hello Bruno \"", "|", "grep", "br", NULL};
	int		expected_coords[][2] = {{0, 3}, {5, 18}, {20, 20}, {22, 25}, {27, 28}};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (!ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		if (splitted->coords[i] && splitted->coords[i][0] == expected_coords[i][0] && splitted->coords[i][1] == expected_coords[i][1])
			right_tokens++;
		i++;
	}
	test.test_ok = (i * 2) == right_tokens;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test2(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 2;
	test.test_input = "echo \"ola eu sou o 'bruno'    \" && echo ' teste 2 ' > \"$HOME\" && echo \"Moro em \\\" Jd. Real \\\"\"";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\"ola eu sou o 'bruno'    \"", "&&", "echo", "' teste 2 '", ">", "\"$HOME\"", "&&", "echo", "\"Moro em \\\" Jd. Real \\\"\"", NULL};
	int		expected_coords[][2] = {{0, 3}, {5, 30}, {32, 33}, {35, 38}, {40, 50}, {52, 52}, {54, 60}, {62, 63}, {65, 68}, {70, 93}};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted->chuncks[i] && !ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		if (splitted->coords[i] && splitted->coords[i][0] == expected_coords[i][0] && splitted->coords[i][1] == expected_coords[i][1])
			right_tokens++;
		i++;
	}
	test.test_ok = (i * 2) == right_tokens;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test3(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 3;
	test.test_input = "echo \" teste dois\"|\"\"\"grudado\" |grep \" ola meu chapa \" ";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\" teste dois\"", "|", "\"grudado\"", "|", "grep", "\" ola meu chapa \"", NULL};
	int		expected_coords[][2] = {{0, 3}, {5, 17}, {18, 18}, {21, 29}, {31, 31}, {32, 35}, {37, 53}};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted->chuncks[i] && !ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		if (splitted->coords[i] && splitted->coords[i][0] == expected_coords[i][0] && splitted->coords[i][1] == expected_coords[i][1])
			right_tokens++;
		i++;
	}
	test.test_ok = (i * 2) == right_tokens;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test4(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 4;
	test.test_input = "echo \" teste dois\"\"grudado\" |grep \" ola meu chapa \" ";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\" teste dois\"\"grudado\"", "|", "grep", "\" ola meu chapa \"", NULL};
	int		expected_coords[][2] = {{0, 3}, {5, 26}, {28, 28}, {29, 32}, {34, 50}};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted->chuncks[i] && !ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		if (splitted->coords[i] && splitted->coords[i][0] == expected_coords[i][0] && splitted->coords[i][1] == expected_coords[i][1])
			right_tokens++;
		i++;
	}
	test.test_ok = (i * 2) == right_tokens;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test5(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 5;
	test.test_input = "echo \" teste dois\"\"\"\"grudado\" |grep \" ola meu chapa \" ";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\" teste dois\"\"grudado\"", "|", "grep", "\" ola meu chapa \"", NULL};
	int		expected_coords[][2] = {{0, 3}, {5, 28}, {30, 30}, {31, 34}, {36, 52}};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted->chuncks[i] && !ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		if (splitted->coords[i] && splitted->coords[i][0] == expected_coords[i][0] && splitted->coords[i][1] == expected_coords[i][1])
			right_tokens++;
		i++;
	}
	test.test_ok = (i * 2) == right_tokens;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test6(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 6;
	test.test_input = "echo 'it'\\''s fine' \" and \\\"ok\\\"\" ; ls -l";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "'it'\\''s fine'", "\" and \\\"ok\\\"\"", ";", "ls", "-l", NULL};
	int		expected_coords[][2] = {{0, 3}, {5, 18}, {20, 32}, {34, 34}, {36, 37}, {39, 40}};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted->chuncks[i] && !ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		if (splitted->coords[i] && splitted->coords[i][0] == expected_coords[i][0] && splitted->coords[i][1] == expected_coords[i][1])
			right_tokens++;
		i++;
	}
	test.test_ok = (i * 2) == right_tokens;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test7(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 7;
	test.test_input = "FOO=\"foo bar\"; echo $FOO \"$FOO\"";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"FOO=\"foo bar\"", ";", "echo", "$FOO", "\"$FOO\"", NULL};
	int		expected_coords[][2] = {{0, 12}, {13, 13}, {15, 18}, {20, 23}, {25, 30}};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted->chuncks[i] && !ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		if (splitted->coords[i] && splitted->coords[i][0] == expected_coords[i][0] && splitted->coords[i][1] == expected_coords[i][1])
			right_tokens++;
		i++;
	}
	test.test_ok = (i * 2) == right_tokens;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test8(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 8;
	test.test_input = "echo \"today is $(date +\"%Y-%m-%d\")\" && printf 'ok\\n'";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\"today is $(date +\"%Y-%m-%d\")\"", "&&", "printf", "'ok\\n'", NULL};
	int		expected_coords[][2] = {{0, 3}, {5, 34}, {36, 37}, {39, 44}, {46, 51}};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted->chuncks[i] && !ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		if (splitted->coords[i] && splitted->coords[i][0] == expected_coords[i][0] && splitted->coords[i][1] == expected_coords[i][1])
			right_tokens++;
		i++;
	}
	test.test_ok = (i * 2) == right_tokens;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test9(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 9;
	test.test_input = "out=`echo foo $(echo \"bar baz\")` ; echo \"$out\"";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"out=", "`", "echo foo ", "$(", "echo \"bar baz\"", ")", "`", ";", "echo", "\"$out\"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted->chuncks[i] && !ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test10(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 10;
	test.test_input = "command 2>&1 > file.txt 1>>log.txt";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"command", "2", ">&", "1", ">", "file.txt", "1", ">>", "log.txt", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted->chuncks[i] && !ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = i == right_tokens;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test11(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 11;
	test.test_input = "echo \\*.c";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\\*.c", NULL};
	right_tokens = 0;
	i = 0;

	int splitted_expected_len = 0;
	while (expected[splitted_expected_len])
		++splitted_expected_len;
	while (expected[i])
	{
		if (!splitted->chuncks[i])
			break ;
		if (!ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = right_tokens == splitted_expected_len;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test12(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 12;
	test.test_input = "echo 'bruno ''fernandes' 'valero''nunes'";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "'bruno ''fernandes'", "'valero''nunes'", NULL};
	right_tokens = 0;
	i = 0;

	int splitted_expected_len = 0;
	while (expected[splitted_expected_len])
		++splitted_expected_len;
	while (expected[i])
	{
		if (!splitted->chuncks[i])
			break ;
		if (!ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = right_tokens == splitted_expected_len;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test13(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 13;
	test.test_input = "echo bruno'fernandes' 'valero'nunes";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "bruno'fernandes'", "'valero'nunes", NULL};
	right_tokens = 0;
	i = 0;

	int splitted_expected_len = 0;
	while (expected[splitted_expected_len])
		++splitted_expected_len;
	while (expected[i])
	{
		if (!splitted->chuncks[i])
			break ;
		if (!ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = right_tokens == splitted_expected_len;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}

static void	test14(void)
{
	t_test				test;
	t_splited_prompt	*splitted;
	int					i;
	int					right_tokens;

	test.teste_number = 14;
	test.test_input = "echo \"bruno\"'fernandes' 'valero'\"nunes\"";
	splitted = ft_refined_splitter(test.test_input);
	char	*expected[] = {"echo", "\"bruno\"'fernandes'", "'valero'\"nunes\"", NULL};
	right_tokens = 0;
	i = 0;

	int splitted_expected_len = 0;
	while (expected[splitted_expected_len])
		++splitted_expected_len;
	while (expected[i])
	{
		if (!splitted->chuncks[i])
			break ;
		if (!ft_strncmp(expected[i], splitted->chuncks[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	test.test_ok = right_tokens == splitted_expected_len;
	print_test_and_result(test, print_result, splitted->chuncks);
	splitted->destroy(&splitted);
}
