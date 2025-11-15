/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:36:46 by ighannam          #+#    #+#             */
/*   Updated: 2025/11/13 16:47:02 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>

void	test_expand(char *input, t_linkedlist_array *env)
{
	char *expanded = ft_expand_var(input, env);
	printf("Input: %-30s | Output: %s\n", input, expanded);
	free(expanded);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_linkedlist_array *env;

	// inicializa o ambiente com variáveis padrão
	env = ft_init_ht_env(envp);

	printf("===== Testes básicos =====\n");
	test_expand("$USER", env);               // esperado: nome de usuário
	test_expand("$HOME", env);               // esperado: caminho home
	test_expand("$PATH", env);               // esperado: /usr/bin:/bin
	test_expand("$$", env);                  // esperado: pid do minishell
	test_expand("$?", env);                  // esperado: status de saída atual

	printf("\n===== Testes após mudanças =====\n");
	ft_set(env, "USER=guest");
	test_expand("$USER", env); // esperado: guest

	ft_unset(env, "HOME");
	test_expand("$HOME", env); // esperado: vazio

	test_expand("$?", env); // deve refletir último status

	printf("\n===== Limpeza =====\n");
	env->destroy(&env, ft_free_item_ht_env);
	return 0;
}
