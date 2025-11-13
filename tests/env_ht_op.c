/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ht_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:02:13 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/12 13:47:31 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <string.h>

static void	test_export_basic(t_linkedlist_array *ht_env);
static void	test_export_update(t_linkedlist_array *ht_env);
static void	test_unset(t_linkedlist_array *ht_env);
static void	test_env_print(t_linkedlist_array *ht_env);
static void	test_edge_cases(t_linkedlist_array *ht_env);

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_linkedlist_array *ht_env = ft_init_ht_env(envp);

	printf("\n===== TEST 1: export básico =====\n");
	test_export_basic(ht_env);

	printf("\n===== TEST 2: export (update valor existente) =====\n");
	test_export_update(ht_env);

	printf("\n===== TEST 3: unset =====\n");
	test_unset(ht_env);

	printf("\n===== TEST 4: env =====\n");
	test_env_print(ht_env);

	printf("\n===== TEST 5: casos limite =====\n");
	test_edge_cases(ht_env);

	ht_env->destroy(&ht_env, ft_free_item_ht_env);
	return (0);
}

/* ========================================================= */

static void	test_export_basic(t_linkedlist_array *ht_env)
{
	ft_export(ht_env, "TEST1=teste");
	t_linkedlist_node *node = (t_linkedlist_node *)ft_find_ht(ht_env, "TEST1");

	if (!node)
		printf("❌ TEST1 não foi encontrado!\n");
	else
	{
		t_ht *found = (t_ht *)(node->content);
		t_env_value *value = (t_env_value *)found->value;
		printf("✅ TEST1 encontrado com valor: '%s'\n", value->value);
	}
}

/* ========================================================= */

static void	test_export_update(t_linkedlist_array *ht_env)
{
	ft_export(ht_env, "TEST1=atualizado");
	t_linkedlist_node *node = (t_linkedlist_node *)ft_find_ht(ht_env, "TEST1");

	if (!node)
		printf("❌ TEST1 não foi encontrado após update!\n");
	else
	{
		t_ht *found = (t_ht *)(node->content);
		t_env_value *value = (t_env_value *)found->value;
		if (strcmp(value->value, "atualizado") == 0)
			printf("✅ TEST1 foi atualizado corretamente.\n");
		else
			printf("❌ TEST1 valor incorreto: '%s'\n", value->value);
	}
}

/* ========================================================= */

static void	test_unset(t_linkedlist_array *ht_env)
{
	ft_unset(ht_env, "TEST1");
	t_linkedlist_node *node = (t_linkedlist_node *)ft_find_ht(ht_env, "TEST1");
	if (node)
		printf("❌ TEST1 ainda existe após unset!\n");
	else
		printf("✅ TEST1 removido com sucesso.\n");
}

/* ========================================================= */

static void	test_env_print(t_linkedlist_array *ht_env)
{
	printf("🔹 Chamando ft_env():\n");
	ft_env(ht_env);

	printf("🔹 Chamando ft_export(NULL): (ordem alfabética esperada)\n");
	ft_export(ht_env, NULL);
}

/* ========================================================= */

static void	test_edge_cases(t_linkedlist_array *ht_env)
{
	printf("\n🧪 Teste: variável sem valor\n");
	ft_export(ht_env, "EMPTY");
	t_linkedlist_node *node = (t_linkedlist_node *)ft_find_ht(ht_env, "EMPTY");
	if (!node)
		printf("❌ 'EMPTY' não foi criada.\n");
	else
		printf("✅ 'EMPTY' criada sem valor.\n");

	printf("\n🧪 Teste: unset variável inexistente\n");
	ft_unset(ht_env, "INEXISTENTE");
	printf("✅ Nenhum crash ao tentar remover variável inexistente.\n");

	printf("\n🧪 Teste: set variável nova via ft_set()\n");
	ft_set(ht_env, "NEW=ok");
	node = (t_linkedlist_node *)ft_find_ht(ht_env, "NEW");
	if (node)
		printf("✅ NEW criada com sucesso.\n");
	else
		printf("❌ NEW não encontrada após ft_set().\n");

	printf("\n🧪 Teste: update via ft_set()\n");
	ft_set(ht_env, "NEW=atualizada");
	node = (t_linkedlist_node *)ft_find_ht(ht_env, "NEW");
	if (node)
	{
		t_ht *found = (t_ht *)(node->content);
		t_env_value *value = (t_env_value *)found->value;
		printf("Valor de NEW: '%s'\n", value->value);
	}
}
