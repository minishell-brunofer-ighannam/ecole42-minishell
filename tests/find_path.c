/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:20:15 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/12 15:54:25 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================================
// Prototypes
// ==========================================================
static void	test_basic_commands(t_linkedlist_array *ht_env);
static void	test_nonexistent_command(t_linkedlist_array *ht_env);
static void	test_absolute_and_relative_paths(t_linkedlist_array *ht_env);
static void	test_no_path_variable(void);
static void	print_which_comparison(const char *cmd, const char *path_found);

// ==========================================================
// Main
// ==========================================================
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	printf("============== TESTES ft_find_path ==============\n");

	t_linkedlist_array *ht_env = ft_init_ht_env(envp);

	printf("\n===== TESTE 1: comandos básicos =====\n");
	test_basic_commands(ht_env);

	printf("\n===== TESTE 2: comando inexistente =====\n");
	test_nonexistent_command(ht_env);

	printf("\n===== TESTE 3: caminhos absolutos e relativos =====\n");
	test_absolute_and_relative_paths(ht_env);

	printf("\n===== TESTE 4: sem variável PATH =====\n");
	test_no_path_variable();

	ht_env->destroy(&ht_env, ft_free_item_ht_env);
	return (0);
}

// ==========================================================
// Funções de Teste
// ==========================================================

static void	test_basic_commands(t_linkedlist_array *ht_env)
{
	char *path;

	path = ft_find_path(ht_env, "ls");
	print_which_comparison("ls", path);
	if (path)
		free(path);

	path = ft_find_path(ht_env, "echo");
	print_which_comparison("echo", path);
	if (path)
		free(path);
}

static void	test_nonexistent_command(t_linkedlist_array *ht_env)
{
	char *path = ft_find_path(ht_env, "naocomando");
	print_which_comparison("naocomando", path);

	if (!path)
		printf("✅ comando inexistente tratado corretamente.\n");
	else
	{
		printf("❌ comando inexistente retornou caminho: %s\n", path);
		free(path);
	}
}

static void	test_absolute_and_relative_paths(t_linkedlist_array *ht_env)
{
	char *path;

	path = ft_find_path(ht_env, "/bin/ls");
	print_which_comparison("/bin/ls", path);
	if (path)
		free(path);

	path = ft_find_path(ht_env, "./meu_script.sh");
	print_which_comparison("./meu_script.sh", path);
	if (path)
		free(path);
}

static void	test_no_path_variable(void)
{
	t_linkedlist_array *ht_env = ft_init_ht_env(NULL);

	char *path = ft_find_path(ht_env, "ls");
	print_which_comparison("ls", path);

	if (!path)
		printf("✅ Sem PATH, ls não encontrado (correto).\n");
	else
	{
		printf("❌ Encontrou ls mesmo sem PATH: %s\n", path);
		free(path);
	}

	ht_env->destroy(&ht_env, ft_free_item_ht_env);
}

// ==========================================================
// Função auxiliar: comparação automática com "which"
// ==========================================================
static void	print_which_comparison(const char *cmd, const char *path_found)
{
	char command[256];
	char which_output[512];
	FILE *fp;

	printf("\n🔹 Testando comando: '%s'\n", cmd);
	if (path_found)
		printf("➡️  ft_find_path: %s\n", path_found);
	else
		printf("➡️  ft_find_path: (NULL)\n");

	snprintf(command, sizeof(command), "which %s 2>/dev/null", cmd);
	fp = popen(command, "r");
	if (!fp)
	{
		printf("⚠️ Erro ao executar 'which'.\n");
		return;
	}
	if (fgets(which_output, sizeof(which_output), fp))
	{
		which_output[strcspn(which_output, "\n")] = '\0'; // remove \n
		printf("➡️  which:        %s\n", which_output);
		if (path_found && strcmp(path_found, which_output) == 0)
			printf("✅ Caminhos coincidem!\n");
		else if (!path_found)
			printf("⚠️ ft_find_path não encontrou, mas which sim.\n");
		else
			printf("❌ Caminhos diferentes!\n");
	}
	else
		printf("➡️  which:        (não encontrou)\n");

	pclose(fp);
}


