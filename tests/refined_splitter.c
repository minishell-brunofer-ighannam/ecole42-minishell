/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refined_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:13:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 13:43:40 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

static void	test1(void);
static void	test2(void);
static void	test3(void);
static void	test4(void);

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
}

static void	test1(void)
{
	char	*string;
	char	**splitted;
	int		i;
	int		right_tokens;

	string = "echo \"hello Bruno \" | grep br";
	splitted = ft_refined_splitter(string);
	char	*expected[] = {"echo", "\"hello Bruno \"", "|", "grep", "br", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (!ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	printf("test 1: %s  ", status(i == right_tokens));
	printf("%s%s%s\n", PRINT_LIGHT_BLACK, string, PRINT_BOLD PRINT_GRAY_233);
	printf("%s%s", " >> Result: ", PRINT_RESET PRINT_GRAY_233);
	i = -1;
	while (splitted[++i])
		printf("[%s] ", splitted[i]);
	printf("\n"PRINT_RESET);
	ft_destroy_char_matrix(&splitted);
}

static void	test2(void)
{
	char	*string;
	char	**splitted;
	int		i;
	int		right_tokens;

	string = "echo \"ola eu sou o 'bruno'    \" && echo ' teste 2 ' > \"$HOME\" && echo \"Moro em \\\" Jd. Real \\\"\"";
	splitted = ft_refined_splitter(string);
	char	*expected[] = {"echo", "\"ola eu sou o 'bruno'    \"", "&&", "echo", "' teste 2 '", ">", "\"$HOME\"", "&&", "echo", "\"Moro em \\\" Jd. Real \\\"\"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	printf("test 2: %s  ", status(i == right_tokens));
	printf("%s%s%s\n", PRINT_LIGHT_BLACK, string, PRINT_BOLD PRINT_GRAY_233);
	printf("%s%s", " >> Result: ", PRINT_RESET PRINT_GRAY_233);
	i = -1;
	while (splitted[++i])
		printf("[%s] ", splitted[i]);
	printf("\n"PRINT_RESET);
	ft_destroy_char_matrix(&splitted);
}

static void	test3(void)
{
	char	*string;
	char	**splitted;
	int		i;
	int		right_tokens;

	string = "echo \" teste dois\"|\"grudado\" |grep \" ola meu chapa \" ";
	splitted = ft_refined_splitter(string);
	char	*expected[] = {"echo", "\" teste dois\"", "|", "\"grudado\"", "|", "grep", "\" ola meu chapa \"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	printf("test 3: %s  ", status(i == right_tokens));
	printf("%s%s%s\n", PRINT_LIGHT_BLACK, string, PRINT_BOLD PRINT_GRAY_233);
	printf("%s%s", " >> Result: ", PRINT_RESET PRINT_GRAY_233);
	i = -1;
	while (splitted[++i])
		printf("[%s] ", splitted[i]);
	printf("\n"PRINT_RESET);
	ft_destroy_char_matrix(&splitted);
}

static void	test4(void)
{
	char	*string;
	char	**splitted;
	int		i;
	int		right_tokens;

	string = "echo \" teste dois\"\"grudado\" |grep \" ola meu chapa \" ";
	splitted = ft_raw_splitter(string);
	char	*expected[] = {"echo", "\" teste doisgrudado\"", "|", "grep", "\" ola meu chapa \"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	printf("test 4: %s  ", status(i == right_tokens));
	printf("%s%s%s\n", PRINT_LIGHT_BLACK, string, PRINT_BOLD PRINT_GRAY_233);
	printf("%s%s", " >> Result: ", PRINT_RESET PRINT_GRAY_233);
	i = -1;
	while (splitted[++i])
		printf("[%s] ", splitted[i]);
	printf("\n"PRINT_RESET);
	ft_destroy_char_matrix(&splitted);
}
