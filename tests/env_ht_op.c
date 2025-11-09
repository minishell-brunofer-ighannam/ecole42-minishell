/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ht_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:02:13 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/09 16:29:51 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define ASSERT_EQ_STR(msg, a, b) \
	do { \
		if (!a || !b || strcmp(a, b) != 0) \
			printf("❌ %s\n  got: %s\n  expected: %s\n", msg, a ? a : "(null)", b ? b : "(null)"); \
		else \
			printf("✅ %s\n", msg); \
	} while (0)

#define ASSERT_TRUE(msg, cond) \
	do { \
		if (!(cond)) printf("❌ %s\n", msg); \
		else printf("✅ %s\n", msg); \
	} while (0)


// Função auxiliar: captura saída de uma função que imprime no stdout
static char	*capture_stdout(void (*func)(t_env **), t_env **env)
{
	int		fd[2];
	int		save_stdout;
	char	buffer[8192];
	ssize_t	n;
	char	*out;

	pipe(fd);
	save_stdout = dup(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);

	func(env);

	fflush(stdout);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);

	n = read(fd[0], buffer, sizeof(buffer) - 1);
	close(fd[0]);
	if (n <= 0)
		return (strdup(""));
	buffer[n] = '\0';
	out = strdup(buffer);
	return (out);
}

// 🔧 Testes individuais
static void	test_export_and_find(void)
{
	extern char **environ;
	t_env **env = ft_init_ht(environ);

	ft_export(env, "TESTKEY", "42");
	char *val = ft_find_env_value("TESTKEY", env);
	ASSERT_EQ_STR("export + find_env_value", val, "42");
}

static void	test_unset(void)
{
	extern char **environ;
	t_env **env = ft_init_ht(environ);

	ft_export(env, "HELLO", "WORLD");
	ft_unset(env, "HELLO");
	char *val = ft_find_env_value("HELLO", env);
	ASSERT_TRUE("unset remove variable", val == NULL);
}

static void	test_env_output(void)
{
	extern char **environ;
	t_env **env = ft_init_ht(environ);

	char *output = capture_stdout(ft_env, env);
	ASSERT_TRUE("env output contains PATH", strstr(output, "PATH=") != NULL);
	free(output);
}

// 🚀 Main de testes
int	main(void)
{
	printf("==== TESTES DE FUNÇÕES ENV ====\n\n");

	test_export_and_find();
	test_unset();
	test_env_output();

	printf("\n==== FIM DOS TESTES ====\n");
	return (0);
}
