/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:13:48 by valero            #+#    #+#             */
/*   Updated: 2025/11/07 17:38:44 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

static void	test1(void);
static void	test2(void);

int	main(int argc, char **argv)
{
	char	**splitted_argv;
	int		i;

	splitted_argv = NULL;
	if (argc >= 2)
	{
		splitted_argv = ft_raw_splitter(argv[1]);
		i = -1;
		while (splitted_argv[++i])
			printf("[%s] ", splitted_argv[i]);
		printf("\n");
		ft_destroy_char_matrix(&splitted_argv);
	}
	test1();
	test2();
}

static void	test1(void)
{
	char	**splitted;
	int		i;
	int		right_tokens;

	splitted = ft_raw_splitter("echo \"hello Bruno \" | grep br");
	char	*expected[] = {"echo", "\"hello Bruno \"", "|", "grep", "br", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (!ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	printf("test 1: %s\n", status(i == right_tokens));
	ft_destroy_char_matrix(&splitted);
}

static void	test2(void)
{
	char	**splitted;
	int		i;
	int		right_tokens;

	splitted = ft_raw_splitter("echo \"ola eu sou o 'bruno'    \" | grep -E \"eu*+\" > teste.txt && echo ' teste 2 ' > \"$HOME\" && echo \"Moro em \\\" Jd. Real \\\"\"");
	char	*expected[] = {"echo", "\"ola eu sou o 'bruno'    \"", "|", "grep", "-E", "\"eu*+\"", ">", "teste.txt", "&&", "echo", "' teste 2 '", ">", "\"$HOME\"", "&&", "echo", "\"Moro em \\\" Jd. Real \\\"\"", NULL};
	right_tokens = 0;
	i = 0;
	while (expected[i])
	{
		if (splitted[i] && !ft_strncmp(expected[i], splitted[i], ft_strlen(expected[i]) + 1))
			right_tokens++;
		i++;
	}
	printf("test 2: %s\n", status(i == right_tokens));
	ft_destroy_char_matrix(&splitted);
}
