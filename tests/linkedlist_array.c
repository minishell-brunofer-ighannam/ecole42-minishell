/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:41:35 by valero            #+#    #+#             */
/*   Updated: 2025/11/17 02:42:08 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/data_structures/data_structures.h"
#include "tests.h"

static void	test_create_linkedlist_array(void);
static void	test_push_elements(void);
static void	test_destroy_linkedlist_array(void);
void		test_push_invalid_index(void);
static void	test_empty_array(void);

int	main(void)
{
	test_create_linkedlist_array();
	test_push_elements();
	test_destroy_linkedlist_array();
	test_push_invalid_index();
	test_empty_array();
}

static void	test_create_linkedlist_array(void)
{
	int					tests_ok;
	t_test				test;
	t_linkedlist_array	*arr;
	int					size;

	test.teste_number = 1;
	test.test_input = "create linkedlist_array";
	tests_ok = 0;
	size = 3;
	arr = ft_new_linkedlist_array(size);
	// Testa se a estrutura foi criada
	tests_ok += arr != NULL;
	tests_ok += arr->size == size;
	tests_ok += arr->nodes_amount == 0;
	tests_ok += arr->push != NULL;
	tests_ok += arr->destroy != NULL;
	// Testa se todas as listas foram inicializadas
	for (int i = 0; i < size; i++) {
		tests_ok += arr->list[i] != NULL;
	}
	arr->destroy(&arr, free);
	tests_ok += arr == NULL; // Verifica se destruição zerou o ponteiro
	test.test_ok = tests_ok == 6 + size;
	print_test(test);
}

static void	test_push_elements(void)
{
	int					tests_ok;
	t_test				test;
	t_linkedlist_array	*arr;
	int					*a;
	int					*b;

	test.teste_number = 2;
	test.test_input = "push elements in linkedlist_array";
	tests_ok = 0;
	arr = ft_new_linkedlist_array(2);
	a = malloc(sizeof(int));
	b = malloc(sizeof(int));
	*a = 10;
	*b = 20;
	arr->push(arr, 0, a); // adiciona na lista 0
	arr->push(arr, 1, b); // adiciona na lista 1
	// Verifica se nodes_amount aumentou
	tests_ok += arr->nodes_amount == 2;
	// Opcional: verificar conteúdo das listas
	tests_ok += *(int*)arr->list[0]->first->content == 10;
	tests_ok += *(int*)arr->list[1]->first->content == 20;
	arr->destroy(&arr, free);
	tests_ok += arr == NULL;
	test.test_ok = tests_ok == 4;
	print_test(test);
}

static void	test_destroy_linkedlist_array(void)
{
	int					tests_ok;
	t_test				test;
	t_linkedlist_array	*arr;
	int					*a;

	test.teste_number = 2;
	test.test_input = "destroy linkedlist_array";
	tests_ok = 0;
	arr = ft_new_linkedlist_array(2);
	a = malloc(sizeof(int));
	*a = 5;
	arr->push(arr, 0, a);
	arr->destroy(&arr, free);
	tests_ok += arr == NULL; // ponteiro principal deve ser NULL
	// Se tentar acessar arr->list ou arr->size aqui, deve dar erro (mas não testamos em C unitário)
	test.test_ok = tests_ok == 1;
	print_test(test);
}

void	test_push_invalid_index(void)
{
	int					tests_ok;
	t_test				test;
	t_linkedlist_array	*arr;
	int					*x;
	t_linkedlist_node	*ret;

	test.teste_number = 2;
	test.test_input = "push invalid index on linkedlist_array";
	tests_ok = 0;
	arr = ft_new_linkedlist_array(2);
	x = malloc(sizeof(int));
	*x = 42;
	// Deve evitar crash; depende da implementação se retorna NULL ou aborta
	ret = arr->push(arr, 3, x); // índice 3 é inválido
	if (!ret)
		free(x);
	tests_ok += ret == NULL;
	arr->destroy(&arr, free);
	tests_ok += arr == NULL;
	test.test_ok = tests_ok == 2;
	print_test(test);
}

static void	test_empty_array(void)
{
	int					tests_ok;
	t_test				test;
	t_linkedlist_array	*arr;

	test.teste_number = 2;
	test.test_input = "empty linkedlist_array";
	tests_ok = 0;
	arr = ft_new_linkedlist_array(0);
	tests_ok += arr != NULL;
	tests_ok += arr->size == 0;
	tests_ok += arr->nodes_amount == 0;
	arr->destroy(&arr, free);
	tests_ok += arr == NULL;
	test.test_ok = tests_ok == 4;
	print_test(test);
}
